#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <video.h>
#include <interrupts.h>
#include <keyboard.h>
#include <rtc-driver.h>
#include <syscalls.h>

#define SCRSVR_SEC 10

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static const void * shellModuleAddress = (void*)0x400000;
static const void * tplModuleAddress = (void*)0x800000;

int timer = 0;

typedef int (*EntryPoint)(unsigned int pcount, char * pgname[], void * pgptrs[]);

void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{
	/* THIS HAS TO BE IN THE SAME ORDER THE PACKER PACKS IT OR
	 * IT BREAKS, LIKE, *REALLY* BAD.
	 */
	void * moduleAddresses[] = {
	    shellModuleAddress,
	    tplModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	clearBSS(&bss, &endOfKernel - &bss);
	return getStackBase();
}

void wake_up(void)
{
	syscall_wake();
	timer = 0;
}

void pit_irq(int irq)
{
	if (timer < SCRSVR_SEC * (1000 / 55)) {
		timer++;
	} else {
		syscall_pause();
	}
}

void kbrd_irq_with_activity(int irq)
{
	wake_up();
	kbrd_irq(irq);
}

int main()
{	
	/* driver initialization */
	/* set up IDTs & int80h */

	install_syscall_handler((IntSysHandler) &int80h);
	install_hw_handler((IntHwHandler) &kbrd_irq_with_activity, INT_KEYB);
	install_hw_handler((IntHwHandler) &pit_irq, INT_PIT);
	install_interrupts();

	kbrd_install();
	vid_clr();
	

	/* these are the PUBLICLY ACCESSIBLE modules */
	void * moduleAddresses[] = {
		tplModuleAddress
	};

	char * moduleNames[] = {
		"template"
	};

	/* call shell */
	uint8_t modules = sizeof(moduleNames) / sizeof(char *);
    ((EntryPoint)shellModuleAddress)(modules, moduleNames, moduleAddresses);

    vid_print("\nHalting", 8);
	return 0;
}
