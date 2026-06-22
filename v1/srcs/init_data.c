#include "../includes/collision.h"

static void	get_alloc_sizes(t_tmp_alloc_sizes *t)
{
	t->cells_count = (MAP_W / CELL_SIZE) * (MAP_H / CELL_SIZE);
	t->cells_size = align16(t->cells_count * sizeof(int32_t));
	t->coords_size = align16(N_PARTICULES * sizeof(t_xy));
	t->next_size = align16(N_PARTICULES * sizeof(int32_t));
}

bool	init_data(t_data *d)
{
	t_tmp_alloc_sizes tmp_sizes;

	get_alloc_sizes(&tmp_sizes);

	// init arena;
	d->arena.offset = 0;
	d->arena.capacity = (tmp_sizes.coords_size * 2) + tmp_sizes.cells_size + tmp_sizes.next_size;
	d->arena.memory = mmap(NULL, d->arena.capacity, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (d->arena.memory == MAP_FAILED)
		return (false);

	// init data
	d->cols = MAP_W / CELL_SIZE;
	d->rows = MAP_H / CELL_SIZE;
	d->n_particle = N_PARTICULES;
	d->cell_count = tmp_sizes.cells_count;

	// assign contiguous memory to the structure
	d->cell_head = arena_allocator(tmp_sizes.cells_size, &d->arena);
	d->next = arena_allocator(tmp_sizes.next_size, &d->arena);
	d->pos = arena_allocator(tmp_sizes.coords_size, &d->arena);
	d->vel = arena_allocator(tmp_sizes.coords_size, &d->arena);

	// if one condition is valid i am a bad at maths
	if (!d->cell_head || !d->pos || !d->vel || !d->next)
	{
		munmap(d->arena.memory, d->arena.capacity);
		return (false);
	}
	return (true);
}
