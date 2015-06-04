#include <interrupts.h>
#include <lib.h>


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
extern void idt_pic_slave_eoi(char eoi);
extern void idt_pic_master_eoi(char eoi);
extern void idt_pic_slave_mask(char mask);
extern void idt_pic_master_mask(char mask);

extern void _irq_syscall_handler(void);

extern void _irq_20h_handler(void);
extern void _irq_21h_handler(void);
extern void _irq_22h_handler(void);
extern void _irq_23h_handler(void);
extern void _irq_24h_handler(void);
extern void _irq_25h_handler(void);
extern void _irq_26h_handler(void);
extern void _irq_27h_handler(void);
extern void _int80h(void);

void irq_handler(int irq);


struct IDT_Entry * IDT;
IDT_Handler handlers[IDT_SIZE];
struct IDT_Register idtr;


void syscall(void)
{
	_int80h();
}

void irq_handler(int irq)
{
	uint16_t index = irq % (uint16_t) IDT_SIZE;

	if (handlers[index] == (IDT_Handler *) 0) {
		return;
	}

	_cli();
	IDT_Handler handler = handlers[index];
	(handler)(irq);
	_sti();
}

static void install_IDT_entry(struct IDT_Entry * table, unsigned int idx, void (*handler)(void), uint16_t flags)
{
	table[idx % IDT_SIZE].z1 = 0;
	table[idx % IDT_SIZE].z2 = 0;

	table[idx % IDT_SIZE].type = flags;
	table[idx % IDT_SIZE].selector = 8; // GDT Entry.

	table[idx % IDT_SIZE].offset_l = (((uint64_t) handler) & 0xFFFF);
	table[idx % IDT_SIZE].offset_m = (((uint64_t) handler) >> 16) & 0xFFFF;
	table[idx % IDT_SIZE].offset_h = (((uint64_t) handler) >> 32) & 0xFFFFFFFF;
}

void install_IDTR(void)
{
	struct IDT_Register orig;
	_cli();

	idtr.limit = IDT_SIZE;
	idtr.offset = IDT;

	_sidt(&idtr);

	memset(handlers, 0, sizeof(handlers));

	idt_pic_master_mask(0);
	idt_pic_slave_mask(0);

	idt_pic_master_eoi(0x20);
	idt_pic_slave_eoi(0x70);
	
	install_IDT_entry((struct IDT_Entry *) idtr.offset, 0x80, &_irq_syscall_handler, IDTE_HW);

	/* move interrupts to 0x20 (start of non-reserved addrs.) */
	install_IDT_entry(idtr.offset, 0x20, &_irq_20h_handler, IDTE_HW);
	install_IDT_entry(idtr.offset, 0x21, &_irq_21h_handler, IDTE_HW);
	install_IDT_entry(idtr.offset, 0x22, &_irq_22h_handler, IDTE_HW);
	install_IDT_entry(idtr.offset, 0x23, &_irq_23h_handler, IDTE_HW);
	install_IDT_entry(idtr.offset, 0x24, &_irq_24h_handler, IDTE_HW);
	install_IDT_entry(idtr.offset, 0x25, &_irq_25h_handler, IDTE_HW);
	install_IDT_entry(idtr.offset, 0x26, &_irq_26h_handler, IDTE_HW);
	install_IDT_entry(idtr.offset, 0x27, &_irq_27h_handler, IDTE_HW);

	_lidt(&idtr);
	
	_sti();
}

void install_IDT_handler(IDT_Handler * handler, uint16_t interrupt)
{
	uint16_t index = interrupt % (uint16_t) IDT_SIZE;
	handlers[index] = handler;
}