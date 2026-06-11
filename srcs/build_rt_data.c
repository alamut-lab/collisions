#include "../includes/collision.h"

/*
	insert a particules by pushing the current value in cell head to next 
	then inserting the current idx into cell head, 
	the first iteration will only change cell_head as next is already at -1, 
	the following multiple p8uish back we can folow the idx pointed by next 
	like a "linked list" (but better i promise)
*/
static void	insert_particle(t_data *d, uint32_t i)
{
	int32_t	cell_x;
	int32_t	cell_y;
	int32_t	cell_id;

	// calculate cell coord
	cell_x = d->pos[i].x / CELL_SIZE;
	cell_y = d->pos[i].y / CELL_SIZE;

	// check_safety
	if (cell_x < 0)
		cell_x = 0;
	if (cell_x >= (int32_t)d->cols)
		cell_x = d->cols - 1;
	if (cell_y < 0)
		cell_y = 0;
	if (cell_y >= (int32_t)d->rows)
		cell_y = d->rows - 1;

	// calculate id on contiguous array
	cell_id = cell_y * d->cols + cell_x;

	// insertion push-back from cell_head
	d->next[i] = d->cell_head[cell_id];
	d->cell_head[cell_id] = i;
}

/*
	build runtime arrays 
	t_data::int32_t *cell_head
	t_data::int32_t *next
*/
void	build_rt_data(t_data *d)
{
	clear_cells(d);
	clear_next(d);
	for (uint32_t i = 0; i < d->n_particle; i++)
		insert_particle(d, i);
}
