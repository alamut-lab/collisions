#include "../includes/collision.h"

/*
    check if a particle is out of bounds;
    if it is the case we invert it's direction and decrease it's velocity of 20%
*/
void    apply_bounds_to_particle(t_data *d, int32_t i)
{
    if (d->pos[i].x < R)
    {
        d->pos[i].x = R;
        d->vel[i].x = -(d->vel[i].x * 8) / 10;
    }
    else if (d->pos[i].x > MAP_W - R)
    {
        d->pos[i].x = MAP_W - R;
        d->vel[i].x = -(d->vel[i].x * 8) / 10;
    }
    if (d->pos[i].y < R)
    {
        d->pos[i].y = R;
        d->vel[i].y = -(d->vel[i].y * 8) / 10;
    }
    else if (d->pos[i].y > MAP_H - R)
    {
        d->pos[i].y = MAP_H - R;
        d->vel[i].y = -(d->vel[i].y * 8) / 10;
    }
}

/*
    iterate over the cell content and apply bound to each of it's elements

    immediatly return in case of d->cell_head[cell_id] == -1

    couled be written this way too:

    for (int32_t i = d->cell_head[cell_id]; i != -1; i = d->next[i])
        apply_bounds_to_particle(d, i);

    but to simply demonstrate how to iterate over the array the code is longer
*/
static void    apply_bounds_to_cell(t_data *d, int32_t cell_id)
{
    int32_t i;

    i = d->cell_head[cell_id];
    while (i != -1)
    {
        apply_bounds_to_particle(d, i);
        i = d->next[i];
    }
}

/*
    check if a particle is out of bounds;
    if it is the case we invert it's direction and decrease it's velocity of 20%

    to do so and by efficiency necessity we only check on the border of the map
*/
void    apply_bounds_to_edges(t_data *d)
{
    int32_t x;
    int32_t y;
    int32_t cell_id;

    // printf("01\n");
    // top
    for (x = 0; x < (int32_t)d->cols; x++)
    {
        cell_id = x;
        apply_bounds_to_cell(d, cell_id);
    }
    // printf("02\n");
    // left and right side
    for (y = 1; y < (int32_t)d->rows - 1; y++)
    {
        // left
        cell_id = y * d->cols;
        apply_bounds_to_cell(d, cell_id);
        // right
        cell_id = y * d->cols + (d->cols - 1);
        apply_bounds_to_cell(d, cell_id);
    }
    // printf("03\n");
    // bottom
    for (x = 0; x < (int32_t)d->cols; x++)
    {
        cell_id = (d->rows - 1) * d->cols + x;
        apply_bounds_to_cell(d, cell_id);
    }
}

/*
	update particle pos by executing x_pos += x_vel
	an other methodology could be used instead

    and apply bounds immediatly
*/
void    move_and_apply_bounds(t_data *d)
{
	for (uint32_t i = 0; i < d->n_particle; i++)
	{
		d->pos[i].x += d->vel[i].x;
		d->pos[i].y += d->vel[i].y;
        apply_bounds_to_particle(d, i);
	}
}
