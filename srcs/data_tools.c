#include "../includes/collision.h"

/*
	update particle pos by executing x_pos += x_vel
	an other methodology could be used instead
*/
void    update_positions(t_data *d)
{
	for (uint32_t i = 0; i < d->n_particle; i++)
	{
		d->pos[i].x += d->vel[i].x;
		d->pos[i].y += d->vel[i].y;
	}
}

/*
	set array :
	t_data::int32_t		*cell_head;
	to -1;
*/
void	clear_cells(t_data *d)
{
	for (uint32_t i = 0; i < d->cell_count; i++)
		d->cell_head[i] = -1;
}

/*
	set array :
	t_data::int32_t		*next;
	to -1;
*/
void	clear_next(t_data *d)
{
	for (uint32_t i = 0; i < d->n_particle; i++)
		d->next[i] = -1;
}