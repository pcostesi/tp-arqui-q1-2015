#include <interrupts.h>
#include <lib.h>
#include <stdint.h>

/*
 * See http://wiki.osdev.org/Interrupt_Descriptor_Table
 * for more information about each register and such.
 */

#define IDTE_PRESENT	0x80		/*	Present 				1.......	*/
#define IDTE_DPL_HW 	0x00		/*	Interrupt GATE HW 		.00.....	*/
#define IDTE_DPL_SW		0x60		/*	Interrupt GATE SW 		.11.....	*/
									/*	Storage segment (0) 	...0....	*/
#define IDTE_I_GATE		0x0E		/*	Gate type (32bit)		....1110	*/
#define IDTE_T_GATE		0x0F		/*	Gate type (32bit)		....1111	*/

#define IDTE_HW			(IDTE_PRESENT | IDTE_DPL_HW | IDTE_I_GATE)
#define IDTE_SW			(IDTE_PRESENT | IDTE_DPL_SW | IDTE_I_GATE)


/* The following structs are packed to reflect the arch registers. 
 * zX fields MUST BE SET TO 0 OR... FIRE AND BRIMSTONE,
 * cats and dogs living together.
 */
#pragma pack(push, 1)

struct IDT_Register {
	uint16_t	limit;
	uint64_t	offset;
};


struct IDT_Entry
{
	uint16_t	offset_l,
				selector;
	uint8_t		z1,
				type;
	uint16_t	offset_m;
	uint32_t	offset_h,
				z2;
};

#pragma pack(pop)


extern void _cli(void);
extern void _sti(void);
extern void _lidt(void *);
extern void _sidt(void *);
extern void _halt(void);
extern void idt_pic_slave_set_map(char);
extern void idt_pic_master_set_map(char);
extern void idt_pic_slave_mask(char);
extern void idt_pic_master_mask(char);

extern void _irq_sys_handler(void);

extern void _irq_20h_handler(void);
extern void _irq_21h_handler(void);
extern void _irq_22h_handler(void);
extern void _irq_23h_handler(void);
extern void _irq_24h_handler(void);
extern void _irq_25h_handler(void);
extern void _irq_26h_handler(void);
extern void _irq_27h_handler(void);

extern void _irq_70h_handler(void);
extern void _irq_71h_handler(void);
extern void _irq_72h_handler(void);
extern void _irq_73h_handler(void);
extern void _irq_74h_handler(void);
extern void _irq_75h_handler(void);
extern void _irq_76h_handler(void);
extern void _irq_77h_handler(void);

static inline int _irq_get_hw_index(int irq);

void irq_handler(int irq);
uint64_t sys_handler(uint64_t RDI, uint64_t RSI, uint64_t RDX, uint64_t RCX, uint64_t R8, uint64_t R9);

static IntHwHandler handlers[INT_TABLE_SIZE] = {0};
static IntSysHandler syscall_handler = (void *) 0;
static struct IDT_Register * idtr;


uint64_t sys_handler(uint64_t RDI, uint64_t RSI, uint64_t RDX, uint64_t RCX, uint64_t R8, uint64_t R9)
{
	register uint64_t sysno;

	/* the syscall number is stored in rax */
    __asm__ __volatile__("mov %%rax, %0" : "=r"(sysno)); /* hackity hack la la */
	if (syscall_handler == (void *) 0) {
		return 0;
	}

	return syscall_handler((uint64_t) sysno, RDI, RSI, RDX, RCX, R8, R9);
}

static inline int _irq_get_hw_index(int irq)
{
	if ((irq & IDT_MASTER)) {
		return irq - IDT_MASTER;
	}

	if ((irq & IDT_SLAVE)) {
		return irq - IDT_SLAVE;
	}

	return 0;
}

void irq_handler(int irq)
{
	int index = _irq_get_hw_index(irq);
	IntHwHandler handler;

	if (index == -1) return;
	handler = handlers[index];

	if (handler == (IntHwHandler) 0) return;
	handler(index);
}

static void install_IDT_entry(struct IDT_Entry * table, unsigned int idx,
							  void (*handler)(void), uint16_t flags)
{
	struct IDT_Entry * entry = table + (idx % INT_IDT_SIZE);
	entry->z1 = 0;
	entry->z2 = 0;

	entry->type = flags;
	entry->selector = 8; // GDT Entry.

	entry->offset_l = (((uint64_t) handler) & 0xFFFF);
	entry->offset_m = (((uint64_t) handler) >> 16) & 0xFFFF;
	entry->offset_h = (((uint64_t) handler) >> 32) & 0xFFFFFFFF;
}

void install_interrupts(void)
{
	struct IDT_Entry * table;
	_cli();
	_sidt(idtr);

	/* enable ALL the interrupts! */
	idt_pic_master_mask(0);
	idt_pic_slave_mask(0);

	/* move interrupts to 0x20 and 0x70 (start of non-reserved addrs.) */
	idt_pic_master_set_map(IDT_MASTER);
	idt_pic_slave_set_map(IDT_SLAVE);
	
	table = (struct IDT_Entry *) idtr->offset;

	/* override int80h entry */
	install_IDT_entry(table, 0x80, 			&_irq_sys_handler, IDTE_SW);

	/* override Master HW ints with our own */
	install_IDT_entry(table, INT_PIT, 		&_irq_20h_handler, IDTE_HW);
	install_IDT_entry(table, INT_KEYB, 		&_irq_21h_handler, IDTE_HW);
	/*						 cascade interrupt (not triggered)			*/
	install_IDT_entry(table, INT_COM2, 		&_irq_23h_handler, IDTE_HW);
	install_IDT_entry(table, INT_COM1, 		&_irq_24h_handler, IDTE_HW);
	install_IDT_entry(table, INT_LPT2, 		&_irq_25h_handler, IDTE_HW);
	install_IDT_entry(table, INT_FLOPPY, 	&_irq_26h_handler, IDTE_HW);
	install_IDT_entry(table, INT_LPT1, 		&_irq_27h_handler, IDTE_HW);
	

	/* override Slave HW ints with our own */
	install_IDT_entry(table, INT_CMOS, 		&_irq_70h_handler, IDTE_HW);
	install_IDT_entry(table, INT_SCSI1, 	&_irq_71h_handler, IDTE_HW);
	install_IDT_entry(table, INT_SCSI2, 	&_irq_72h_handler, IDTE_HW);
	install_IDT_entry(table, INT_SCSI3, 	&_irq_73h_handler, IDTE_HW);
	install_IDT_entry(table, INT_MOUSE, 	&_irq_74h_handler, IDTE_HW);
	install_IDT_entry(table, INT_FPU, 		&_irq_75h_handler, IDTE_HW);
	install_IDT_entry(table, INT_ATA1, 		&_irq_76h_handler, IDTE_HW);
	install_IDT_entry(table, INT_ATA2, 		&_irq_77h_handler, IDTE_HW);
	
	_lidt(idtr);
	
	_sti();
}

void install_syscall_handler(IntSysHandler handler)
{
	syscall_handler = handler;
}


void install_hw_handler(IntHwHandler handler, enum INTERRUPT_HW interrupt)
{
	uint16_t index = _irq_get_hw_index(interrupt);
	if (index == -1) return;
	handlers[index] = handler;
}