#include "../includes/collision.h"

#define COLLISION_DIST2 ((2 * R) * (2 * R))

static inline int32_t	sign_i32(int32_t v)
{
	return ((v > 0) - (v < 0));
}

/*
    soon opt for branchless version

	compute hypothenuse with pythagore
    dist2 = vx2 + vy2
    if (collision)
        move by one everything pos and vel
*/
static inline void	resolve_collision(t_data *d, int32_t a, int32_t b)
{
	int32_t	diff_x;
	int32_t	diff_y;
	int32_t	dist2;
	int32_t	sx;
	int32_t	sy;

	diff_x = d->pos[b].x - d->pos[a].x;
	diff_y = d->pos[b].y - d->pos[a].y;
	dist2 = diff_x * diff_x + diff_y * diff_y;
	if (dist2 >= COLLISION_DIST2)
		return ;
	if (dist2 == 0)
	{
		sx = 1;
		sy = 0;
	}
	else
	{
		sx = sign_i32(diff_x);
		sy = sign_i32(diff_y);
	}
	// branch less coord update
	d->pos[a].x -= sx;
	d->pos[b].x += sx;
	d->vel[a].x -= sx;
	d->vel[b].x += sx;
	d->pos[a].y -= sy;
	d->pos[b].y += sy;
	d->vel[a].y -= sy;
	d->vel[b].y += sy;
	apply_bounds_to_particle(d, a);
	apply_bounds_to_particle(d, b);
}

static inline void	solve_cell_self(t_data *d, int32_t cell)
{
	int32_t	i;
	int32_t	j;

	i = d->cell_head[cell];
	while (i != -1)
	{
		j = d->next[i];
		while (j != -1)
		{
			resolve_collision(d, i, j);
			j = d->next[j];
		}
		i = d->next[i];
	}
}

static inline void	solve_cell_pair(t_data *d, int32_t cell_a, int32_t cell_b)
{
	int32_t	i;
	int32_t	j;

	i = d->cell_head[cell_a];
	while (i != -1)
	{
		j = d->cell_head[cell_b];
		while (j != -1)
		{
			resolve_collision(d, i, j);
			j = d->next[j];
		}
		i = d->next[i];
	}
}

/*
    send only the potential collisions particles to the comparision system
    through : void resolve_collision(t_data *d, int32_t a, int32_t b)
	
	solve collisions by checking the :
	"right", "bottom left", "bottom" and "bottom right" cells
*/
void	solve_collisions(t_data *d)
{
	int32_t	x;
	int32_t	y;
	int32_t	cell_id;

	y = 0;
	while (y < (int32_t)d->rows)
	{
		x = 0;
		while (x < (int32_t)d->cols)
		{
			cell_id = y * d->cols + x;

			solve_cell_self(d, cell_id);
            // cmp right +1
			if (x + 1 < (int32_t)d->cols)
				solve_cell_pair(d, cell_id, cell_id + 1);
            // cmp botom -1 0 1
			if (y + 1 < (int32_t)d->rows)
			{
				if (x > 0)
					solve_cell_pair(d, cell_id, cell_id + d->cols - 1);
				solve_cell_pair(d, cell_id, cell_id + d->cols);
				if (x + 1 < (int32_t)d->cols)
					solve_cell_pair(d, cell_id, cell_id + d->cols + 1);
			}
			x++;
		}
		y++;
	}
}