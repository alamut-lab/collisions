#include "../includes/collision.h"

/*
	Linear Congruential Generator -> AKA PSEUDO RANDOM UINT32 GENERATOR
	# define LCG_SEED 123456789
	# define LCG_MULT 1664525u
	# define LCG_INC  1013904223u
*/
static uint32_t	random_LCG(uint32_t *seed, uint32_t mult, uint32_t inc, uint32_t mod)
{
	*seed = ((*seed * mult) + inc);
	return (*seed % mod);
}

void	init_particules(t_data *d)
{
	uint32_t    i;
	uint32_t    seed;

	i = 0;
	seed = LCG_SEED;
	while (i < d->n_particle)
	{
		d->pos[i].x = MAP_W / 2 + (int32_t)(random_LCG(&seed, LCG_MULT, LCG_INC, SPAWN_W) - (SPAWN_W / 2));
		d->pos[i].y = MAP_H / 2 + (int32_t)(random_LCG(&seed, LCG_MULT, LCG_INC, SPAWN_H) - (SPAWN_H / 2));

		// maybe to rework too magic ?!?
		d->vel[i].x = (int32_t)random_LCG(&seed, LCG_MULT, LCG_INC, 7) - 3;
		d->vel[i].y = (int32_t)random_LCG(&seed, LCG_MULT, LCG_INC, 7) - 3;

		if (d->vel[i].x == 0 && d->vel[i].y == 0)
			d->vel[i].x = 1;
		i++;
	}
}