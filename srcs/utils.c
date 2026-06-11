#include "../includes/collision.h"

/*
    ALLIGNEMENT ON MULTIPLE 

	idea        : (myint + 7) & ~0x07;
		
	binary 7    : 0000 0111
	inverse ~7  : 1111 1000

	// lets imagine n = 11
	11 + 7 = 18; // we pass to the next multiple of height;
	(18 & ~7) = (0001 0010 & 1111 1000); // & means we only take 1 when both values are 1

	0001 0010
	1111 1000
	---------
	0001 0000 == 16

	res = 16
*/
size_t	align8(size_t n)
{
	return ((n + 7) & ~7);
}

size_t	align16(size_t n)
{
	return ((n + 15) & ~15);
}
