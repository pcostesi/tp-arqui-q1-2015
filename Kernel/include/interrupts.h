#ifndef _INTERRUPTS_H_
#define _INTERRUPTS_H_ 1

#include <stdint.h>

#define INT_IDT_SIZE	0xFF		/*	256 interrupts for Intel */
#define	IDT_MASTER		0x20
#define IDT_SLAVE		0x70

enum INTERRUPT_HW
{
	INT_PIT 			 = 	IDT_MASTER + 0,	/* Programmable Interrupt Timer Interrupt */
	INT_KEYB 			 = 	IDT_MASTER + 1,	/* Keyboard Interrupt */
											/* Cascade (used internally by the two PICs. never raised) */
	INT_COM2 			 = 	IDT_MASTER + 3,	/* COM2 (if enabled) */
	INT_COM1 			 = 	IDT_MASTER + 4,	/* COM1 (if enabled) */
	INT_LPT2 			 = 	IDT_MASTER + 5,	/* LPT2 (if enabled) */
	INT_FLOPPY 			 = 	IDT_MASTER + 6,	/* Floppy Disk */
	INT_LPT1 			 = 	IDT_MASTER + 7,	/* LPT1 / Unreliable "spurious" interrupt (usually) */
	INT_SPU 			 = 	IDT_MASTER + 7,	/* LPT1 / Unreliable "spurious" interrupt (usually) */

	INT_CMOS 			 = 	IDT_SLAVE + 8,	/* CMOS real-time clock (if enabled) */
	INT_SCSI1 			 = 	IDT_SLAVE + 9,	/* Free for peripherals / legacy SCSI / NIC */
	INT_SCSI2 			 = 	IDT_SLAVE + 10,	/* Free for peripherals / SCSI / NIC */
	INT_SCSI3 			 = 	IDT_SLAVE + 11,	/* Free for peripherals / SCSI / NIC */
	INT_MOUSE 			 = 	IDT_SLAVE + 12,	/* PS2 Mouse */
	INT_FPU 			 = 	IDT_SLAVE + 13,	/* FPU / Coprocessor / Inter-processor */
	INT_ATA1 			 = 	IDT_SLAVE + 14,	/* Primary ATA Hard Disk */
	INT_ATA2 			 = 	IDT_SLAVE + 15	/* Secondary ATA Hard Disk */
};

#define INT_TABLE_SIZE	16


typedef void (* IntHwHandler)(int irq);
typedef int (* IntSysHandler)(int syscall, int RDI, int RSI, int RDX, int RCX, int R8, int R9);

/* I personally find typedefs ugly, as they hide too much details in kernel impl.
 * and break the expectations in forward declaration of structures.
 */
void install_interrupts(void);
void install_hw_handler(IntHwHandler handler, enum INTERRUPT_HW interrupt);
void install_syscall_handler(IntSysHandler handler);

#endif