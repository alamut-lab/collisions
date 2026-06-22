#include "../includes/collisions.h"

static inline int8_t	clamp_i8(int32_t v)
{
	if (v > INT8_MAX)
		return (INT8_MAX);
	if (v < INT8_MIN)
		return (INT8_MIN);
	return ((int8_t)v);
}

static inline void move(t_data *d)
{
	#pragma GCC ivdep
	for (int32_t i = 0; i < N_PARTICLES; i++)
	{
		d->p.px[i] += d->p.vx[i];
		d->p.py[i] += d->p.vy[i];
	}
}

static inline void swap_particles_buffers(t_data *d)
{
	int16_t		*px;
	int16_t		*py;
	int16_t		*vx;
	int16_t		*vy;
	uint16_t	*cell_id;

	px = d->sorted_p.px;
	py = d->sorted_p.py;
	vx = d->sorted_p.vx;
	vy = d->sorted_p.vy;
	cell_id = d->sorted_p.cell_id;

	d->sorted_p.px = d->p.px;
	d->sorted_p.py = d->p.py;
	d->sorted_p.vx = d->p.vx;
	d->sorted_p.vy = d->p.vy;
	d->sorted_p.cell_id = d->p.cell_id;

	d->p.px = px;
	d->p.py = py;
	d->p.vx = vx;
	d->p.vy = vy;
	d->p.cell_id = cell_id;
}

static inline void	avoid_all_zero_velocities(t_data *d)
{
	int32_t	i;

	i = 0;
	while (i < N_PARTICLES)
	{
		if (d->p.vx[i] == 0 && d->p.vy[i] == 0)
		{
			d->p.vx[i] = ((i & 1) ? 1 : -1);
			d->p.vy[i] = ((i & 2) ? 1 : -1);
		}
		i++;
	}
}

void	simulate_frame(t_data *d)
{
	move(d);
	apply_bounds_after_move(d);
	
	sort_particles(d);
	swap_particles_buffers(d);

	solve_collisions(d);
	apply_bounds_to_edges(d);
	avoid_all_zero_velocities(d);
}