#include "../includes/collisions.h"

static inline void	fill_cell_count(int32_t *cell_count, t_particle *p)
{
	int32_t	cell_id;

	memset(cell_count, 0, I32_N_CELL);
	for(int32_t i = 0; i < N_PARTICLES; i++)
	{
		cell_id = p->cell_id[i];
		cell_count[cell_id]++;
	}
}

static inline void	fill_cell_start_offset(t_data *d)
{
	int32_t	last_start;

	last_start = 0;
	for (int32_t i = 0; i < CELL_COUNT; i++)
	{
		d->cell_start[i] = last_start;
		d->cell_index[i] = last_start;
		last_start += d->cell_count[i];
	}
}

static inline void copy_particle(int32_t src_id, int32_t dst_id, t_particle *src, t_particle *dst)
{
	dst->px[dst_id] = src->px[src_id];
	dst->py[dst_id] = src->py[src_id];
	dst->vx[dst_id] = src->vx[src_id];
	dst->vy[dst_id] = src->vy[src_id];
	dst->cell_id[dst_id] = src->cell_id[src_id];
}

void sort_particles(t_data *d)
{
	int32_t	dest_id;
	int32_t	cell_id;

	fill_cell_count(d->cell_count, &d->p);
	fill_cell_start_offset(d);
	for (int32_t i = 0; i < N_PARTICLES; i++)
	{
		cell_id = d->p.cell_id[i];
		dest_id = d->cell_index[cell_id];
		copy_particle(i, dest_id, &d->p, &d->sorted_p);
		d->cell_index[cell_id]++;
	}
}