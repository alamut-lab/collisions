#include "../includes/collisions.h"

static inline uint64_t	now_ns(void)
{
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ((uint64_t)ts.tv_sec * 1000000000ull + ts.tv_nsec);
}

void	run_simulation_benchmark(t_data *d, size_t warm_up)
{
	uint64_t	start;
	uint64_t	end;
	uint64_t	total;
	double		per_frame;
	size_t		i;

	for (i = 0; i < warm_up; i++)
		simulate_frame(d);

	start = now_ns();
	
	for (i = 0; i < N_FRAMES; i++)
		simulate_frame(d);

	end = now_ns();

	total = end - start;
	per_frame = (double)total / (double)N_FRAMES;

	printf("n particles : %d\n", N_PARTICLES);
	printf("frames		: %d\n", N_FRAMES);
	printf("total		: %lu ns\n", total);
	printf("per frame	: %.2f ns\n", per_frame);
	printf("per frame	: %.2f ms\n", per_frame / 1000000.0);
}