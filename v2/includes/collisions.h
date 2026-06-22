#ifndef COLLISIONS_H
# define COLLISIONS_H

/* libs */

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stddef.h>
# include <string.h>
# include <immintrin.h>
# include <math.h>
// for mmap() syscall
# include <sys/mman.h>
// for benchmark
# include <time.h>
// for viz
# include "../mlx/mlx.h"

/* macros */

// common properties
# define N_FRAMES		1000
# define N_PARTICLES	100000
# define MAP_W			1000
# define MAP_H			1000
# define R				2
# define VELOCITY_RANGE	7
# define BOUND_CHECK_EDGE 2
// LCG properties 
# define LCG_SEED		123456789
# define LCG_MULT		1664525u
# define LCG_INC		1013904223u
// calculated over
# define SPAWN_W		(MAP_W / 5)
# define SPAWN_H		(MAP_H / 5)
# define CELL_SIZE		(2 * R)
# define CELL_W			((MAP_W + CELL_SIZE - 1) / CELL_SIZE)
# define CELL_H			((MAP_H + CELL_SIZE - 1) / CELL_SIZE)
# define CELL_COUNT		(CELL_W * CELL_H)
# define COLLISION_DIST (2 * R)
# define COLLISION_DIST2 (COLLISION_DIST * COLLISION_DIST)
// use cell shift to find the cell a particle is in : cell_x = px >> CELL_SHIFT
# define CELL_SHIFT		(__builtin_ctz(CELL_SIZE))
// use the cell mask to find the local x of a particle in a cell : local_x = px & CELL_MASK
# define CELL_MASK 		(CELL_SIZE - 1)

# define I32_N_PARTICLE		(((sizeof(int32_t) * N_PARTICLES) + 15) & ~15)
# define I16_N_PARTICLE		(((sizeof(int16_t) * N_PARTICLES) + 15) & ~15)
# define I32_N_CELL			(((sizeof(int32_t) * CELL_COUNT) + 15) & ~15)
# define I16_N_CELL			(((sizeof(int16_t) * CELL_COUNT) + 15) & ~15)
# define T_PARTICLE_SIZE 	((I16_N_PARTICLE * 5))

# define LUT_SIDE (2 * COLLISION_DIST + 1)

/* structures */

// memory allocator
typedef struct	s_arena
{
	uint8_t		*memory;
	uint64_t	capacity;
	uint64_t	offset;
}				t_arena;

// SOA particles 
typedef struct	s_particle
{
	int16_t		*px;
	int16_t		*py;
	int16_t		*vx;
	int16_t		*vy;
	uint16_t	*cell_id;
}				t_particle;

// runtime data structure
// the goal here is to used the array cell_idx as an iterator
// threw the contiguaous data stucture sorted_p itself soa
typedef struct	s_data
{
	t_particle	p;
	t_particle	sorted_p;

	int32_t		*cell_count;
	int32_t		*cell_start;
	int32_t		*cell_index;
}				t_data;

// viz
# define COLOR_BG 0x000000
# define COLOR_PARTICLE 0xFFFFFF

typedef struct s_vis
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	t_data	*d;
	t_arena	*arena;
	int		frame;
}			t_vis;

// lut
typedef struct s_lut
{
	int8_t	push_x;
	int8_t	push_y;
	int8_t	imp_x;
	int8_t	imp_y;
}	t_lut;

extern t_lut	g_lut_tab[LUT_SIDE][LUT_SIDE];


void	init_lut(void);

/* prototypes */

// tools.c
size_t		align_16(size_t n);
uint32_t	random_LCG(uint32_t *seed, uint32_t mult, uint32_t inc, uint32_t mod);
// arena.c
void		*arena_allocator(size_t n, t_arena *arena);
void		free_arena(t_arena *arena);
// init_data.c
bool		init_data(t_data *d, t_arena *a);
// frame loop
void 		sort_particles(t_data *d);
void		apply_bounds_after_move(t_data *d);
void		apply_bounds_to_edges(t_data *d);
void		solve_collisions(t_data *d);
void		simulate_frame(t_data *d);
// testing
void		run_simulation_benchmark(t_data *d, size_t warm_up);
int			run_visualizer(t_data *d, t_arena *arena);

/* inlined func */

static inline void  update_cell_id(t_data *d, int32_t i)
{
    int32_t c_x;
    int32_t c_y;

    c_x = (d->p.px[i] >> CELL_SHIFT);
    c_y = (d->p.py[i] >> CELL_SHIFT);

	if (c_x < 0)
		c_x = 0;
	else if (c_x >= CELL_W)
		c_x = CELL_W - 1;
	if (c_y < 0)
		c_y = 0;
	else if (c_y >= CELL_H)
		c_y = CELL_H - 1;
    
    d->p.cell_id[i] = c_y * CELL_W + c_x;
}

static inline int32_t	sign_i32(int32_t v)
{
	return ((v > 0) - (v < 0));
}

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
# define RST        "\033[0m"

#endif