#include "../includes/collisions.h"

static inline void run_simulation(t_data *d)
{
	for (int32_t i = 0; i < N_FRAMES; i++)
		simulate_frame(d);
}

int main(int ac, char **av)
{
	t_data	d;
	t_arena	a;

	if (!init_data(&d, &a))
		return (1);

	init_lut();

	if (ac == 1)
		run_simulation(&d);
	else if (ac == 2 && !strcmp(av[1], "bench"))
		run_simulation_benchmark(&d, 100);
	else if (ac == 2 && !strcmp(av[1], "viz"))
		run_visualizer(&d, &a);
	else 
		printf(RED"error fmt\n"RST);

	free_arena(&a);

	return (0);
}