#include "../includes/collisions.h"

static void	init_particles(t_particle *p)
{
	uint32_t	seed;

	seed = LCG_SEED;
	for (int32_t i = 0; i < N_PARTICLES; i++)
	{
		p->px[i] = MAP_W / 2 + (int32_t)(random_LCG(&seed, LCG_MULT, LCG_INC, SPAWN_W) - (SPAWN_W / 2));
		p->py[i] = MAP_H / 2 + (int32_t)(random_LCG(&seed, LCG_MULT, LCG_INC, SPAWN_H) - (SPAWN_H / 2));

		p->vx[i] = (int32_t)random_LCG(&seed, LCG_MULT, LCG_INC, VELOCITY_RANGE) - ( VELOCITY_RANGE / 2);
		p->vy[i] = (int32_t)random_LCG(&seed, LCG_MULT, LCG_INC, VELOCITY_RANGE) - ( VELOCITY_RANGE / 2);

		p->cell_id[i] = ((p->py[i] >> CELL_SHIFT) * CELL_W) + (p->px[i] >> CELL_SHIFT);

		if (p->vx[i] == 0 && p->vy[i] == 0)
			p->vx[i] = 1;
	}
}

static bool	alloc_particle(t_particle *p, t_arena *a)
{
	p->px = arena_allocator(I16_N_PARTICLE, a);
	p->py = arena_allocator(I16_N_PARTICLE, a);
	p->vx = arena_allocator(I16_N_PARTICLE, a);
	p->vy = arena_allocator(I16_N_PARTICLE, a);
	p->cell_id = arena_allocator(I16_N_PARTICLE, a);
	if (!p->px || !p->py || !p->vx || !p->vy || !p->cell_id)
		return (false);
	return (true);
}

bool	init_data(t_data *d, t_arena *a)
{
	a->offset = 0;
	a->capacity = (T_PARTICLE_SIZE * 2) + (I32_N_CELL * 3);
	a->memory = mmap(NULL, a->capacity, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (a->memory == MAP_FAILED)
		return (false);
	if (!alloc_particle(&d->p, a) || !alloc_particle(&d->sorted_p, a))
		return (free_arena(a), false);
	d->cell_count = arena_allocator(I32_N_CELL, a);
	d->cell_start = arena_allocator(I32_N_CELL, a);
	d->cell_index = arena_allocator(I32_N_CELL, a);
	if (!d->cell_count || !d->cell_start || !d->cell_index)
		return (free_arena(a), false);
	init_particles(&d->p);

	return (true);
}
