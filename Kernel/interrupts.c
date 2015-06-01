#include <interrupts.h>

/* The following structs are packed to reflect the arch registers. 
 * zX fields MUST BE SET TO 0 OR... FIRE AND BRIMSTONE,
 * cats and dogs living together.
 */
#pragma pack(push)
#pragma pack (1)

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
