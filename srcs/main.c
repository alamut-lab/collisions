#include "../includes/collision.h"

void simulate_frame(t_data *d)
{
    move_and_apply_bounds(d);
    solve_collisions(d);
    build_rt_data(d);
    apply_bounds_to_edges(d);
}

void run_simulation(t_data *d)
{
    uint32_t frame;

    frame = 0;
    while (frame < N_FRAMES)
    {
        simulate_frame(d);
        frame++;
    }
}

static inline uint64_t	now_ns(void)
{
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ((uint64_t)ts.tv_sec * 1000000000ull + ts.tv_nsec);
}

void	run_simulation_bench(t_data *d)
{
	uint64_t	start;
	uint64_t	end;
	uint64_t	total;
	double		per_frame;
	int			i;

	i = 0;
	while (i < 100)
	{
		simulate_frame(d);
		i++;
	}

	start = now_ns();
	i = 0;
	while (i < N_FRAMES)
	{
		simulate_frame(d);
		i++;
	}
	end = now_ns();

	total = end - start;
	per_frame = (double)total / (double)N_FRAMES;

	printf("frames: %d\n", N_FRAMES);
	printf("total: %lu ns\n", total);
	printf("per frame: %.2f ns\n", per_frame);
	printf("per frame: %.3f ms\n", per_frame / 1000000.0);
}

int main(void)
{
    t_data d;

    if (!init_data(&d))
        return (1);

    init_particules(&d);
    build_rt_data(&d);

	// print_cells(&d);

	if (BENCHMARK == true)
	    run_simulation_bench(&d);
	else
		run_simulation(&d);

    free_data(&d);

    return (0);
}