#include "../includes/collision.h"

/*
	basic allocator, free is not possible
	allocate chunks of memory int he available space
*/
void	*arena_allocator(size_t n, t_arena *arena)
{
	uint8_t *out;

	n = align16(n);
	if (arena->capacity < arena->offset + n)
		return (NULL);
	out = arena->memory + arena->offset;
	arena->offset += n;
	return ((void *)out);
}

/*
	I thihnk you got it
*/
void    free_data(t_data *d)
{
	if (d->arena.memory && d->arena.memory != MAP_FAILED)
		munmap(d->arena.memory, d->arena.capacity);
	d->arena.memory = NULL;
	d->arena.capacity = 0;
	d->arena.offset = 0;
}