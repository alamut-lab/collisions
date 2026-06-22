# include "../includes/collisions.h"

void	*arena_allocator(size_t n, t_arena *arena)
{
	uint8_t	*out;

	n = align_16(n);
	if (arena->capacity < arena->offset + n)
		return (NULL);
	out = arena->memory + arena->offset;
	arena->offset += n;
	return ((void *)out);
}

void	free_arena(t_arena *arena)
{
	if (arena->memory && arena->memory != MAP_FAILED)
		munmap(arena->memory, arena->capacity);
	arena->memory = NULL;
	arena->capacity = 0;
	arena->offset = 0;
}