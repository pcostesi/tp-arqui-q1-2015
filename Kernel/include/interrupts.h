#ifndef _INTERRUPTS_H_
#define _INTERRUPTS_H_ 1

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

#define IDT_SIZE		0x80		/*	We should at least handle int80h!	*/

/* The following structs are packed to reflect the arch registers. 
 * zX fields MUST BE SET TO 0 OR... FIRE AND BRIMSTONE,
 * cats and dogs living together.
 */
#pragma pack(push)
#pragma pack (1)

struct IDT_Register {
	uint16_t	limit;
	uint64_t	offset;
};

#pragma pack(pop)

void (* IDT_Handler)(void);

/* I personally find typedefs ugly, as they hide too much details in kernel impl.
 * and break the expectations in forward declaration of structures.
 */
void install_IDTR(struct IDT_Register * idtr);
void install_IDT_handler((IDT_Handler *) handler, uint16_t interrupt);

void _cli(void);
void _sti(void);
void _halt(void);

#endif