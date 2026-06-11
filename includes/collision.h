#ifndef COLLISION_H
# define COLLISION_H

/* includes */

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stddef.h>
# include <string.h>
# include <sys/mman.h>
# include <time.h>


/* macros */

/* please enjoy modifying this values (reasonably of course) */
# define N_FRAMES 1000
# define MAP_W 1000
# define MAP_H 1000
# define N_PARTICULES 100000
# define LCG_SEED 123456789
# define LCG_MULT 1664525u
# define LCG_INC  1013904223u

/* please do not modify this values */
# define SPAWN_W (MAP_W / 5)
# define SPAWN_H (MAP_H / 5)
# define R 2
# define CELL_SIZE (2 * R)

# ifndef BENCHMARK
#  define BENCHMARK false
# endif

/* data */

typedef struct  s_arena
{
	uint8_t		*memory;
	size_t		capacity;
	size_t		offset;
}               t_arena; // 64 * 3 + 64(pad) = 32

typedef struct	s_xy
{
	int16_t		x;			// 2
	int16_t		y;			// 2
}				t_xy; // 4

typedef struct	s_data
{
	t_arena		arena;			// 32

	t_xy		*pos;			// 8
	t_xy		*vel;			// 8

	int32_t		*cell_head;		// 8
	int32_t		*next;			// 8

	uint32_t	n_particle;		// 4
	uint32_t	cell_count;		// 4
	uint32_t	cols;			// 4
	uint32_t	rows;			// 4
}				t_data;	// 80

// trash
typedef struct	s_tmp_alloc_sizes
{
	size_t		cells_count;
	size_t		cells_size;
	size_t		coords_size;
	size_t		next_size;
}				t_tmp_alloc_sizes;

/* protos */

/* utils.c */
size_t	align16(size_t n);
size_t	align8(size_t n);

/* data_tools.c */
void	clear_next(t_data *d);
void	clear_cells(t_data *d);
void    update_positions(t_data *d);

/* arena.c */
void	*arena_allocator(size_t n, t_arena *arena);
void 	free_data(t_data *d);

/* init_data.c */
bool	init_data(t_data *d);

/* init_particules.c */
void	init_particules(t_data *d);

/* update.c */
void	build_rt_data(t_data *d);

/* apply_bounds.c */
void    apply_bounds_to_edges(t_data *d);
void    move_and_apply_bounds(t_data *d);
void	apply_bounds_all(t_data *d);
void    apply_bounds_to_particle(t_data *d, int32_t i);

/* collisions.c */
void	solve_collisions(t_data *d);

/* print.c */
void    print_data(t_data *d);
void    print_cells(t_data *d);
void	print_pos(t_data *d);
void 	print_next_array(t_data *d);


/* colors */
# define BLACK      "\033[0;30m"
# define RED        "\033[0;31m"
# define GREEN      "\033[0;32m"
# define YELLOW     "\033[0;33m"
# define BLUE       "\033[0;34m"
# define MAGENTA    "\033[0;35m"
# define CYAN       "\033[0;36m"
# define WHITE      "\033[0;37m"
# define BRED       "\033[1;31m"
# define BGREEN     "\033[1;32m"
# define BYELLOW    "\033[1;33m"
# define BBLUE      "\033[1;34m"
# define BMAGENTA   "\033[1;35m"
# define BCYAN      "\033[1;36m"
# define BWHITE     "\033[1;37m"
# define DIM        "\033[2m"
# define ITALIC     "\033[3m"
# define BOLD       "\033[1m"
# define UNDERLINE  "\033[4m"
# define BLINK      "\033[5m"
# define RESET      "\033[0m"

#endif