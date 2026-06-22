# include "../includes/collisions.h"

size_t		align_16(size_t n)
{
	return ((n + 15) & ~15);
}

uint32_t	random_LCG(uint32_t *seed, uint32_t mult, uint32_t inc, uint32_t mod)
{
	*seed = ((*seed * mult)+ inc);
	return (*seed % mod);
}