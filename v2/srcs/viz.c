#include "../includes/collisions.h"

void	put_pixel(t_vis *v, int x, int y, uint32_t color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= MAP_W || y >= MAP_H)
		return ;
	dst = v->addr + (y * v->line_len) + (x * (v->bpp / 8));
	*(uint32_t *)dst = color;
}

void	clear_image(t_vis *v)
{
	int	x;
	int	y;

	y = 0;
	while (y < MAP_H)
	{
		x = 0;
		while (x < MAP_W)
		{
			put_pixel(v, x, y, COLOR_BG);
			x++;
		}
		y++;
	}
}

void	draw_particle(t_vis *v, int cx, int cy)
{
	int	x;
	int	y;

	y = cy - R;
	while (y <= cy + R)
	{
		x = cx - R;
		while (x <= cx + R)
		{
			if ((x - cx) * (x - cx) + (y - cy) * (y - cy) <= R * R)
				put_pixel(v, x, y, COLOR_PARTICLE);
			x++;
		}
		y++;
	}
}

void	draw_particles(t_vis *v)
{
	uint32_t	i;

	i = 0;
	while (i < N_PARTICLES)
	{
		draw_particle(v, v->d->p.px[i], v->d->p.py[i]);
		i++;
	}
}

int	close_window(t_vis *v)
{
	if (v->img)
		mlx_destroy_image(v->mlx, v->img);
	if (v->win)
		mlx_destroy_window(v->mlx, v->win);
    free_arena(v->arena);
	exit(0);
	return (0);
}

int	key_press(int keycode, t_vis *v)
{
	if (keycode == 65307) // Escape Linux/X11
		close_window(v);
	return (0);
}

int	render_frame(t_vis *v)
{
	if (v->frame >= N_FRAMES)
		close_window(v);

	simulate_frame(v->d);
	clear_image(v);
	draw_particles(v);
	mlx_put_image_to_window(v->mlx, v->win, v->img, 0, 0);
	v->frame++;
	return (0);
}

int	run_visualizer(t_data *d, t_arena *arena)
{
	t_vis	v;

	v.frame = 0;
	v.d = d;
    v.arena = arena;
	v.mlx = mlx_init();
	if (!v.mlx)
		return (0);
	v.win = mlx_new_window(v.mlx, MAP_W, MAP_H, "collisions visualizer");
	if (!v.win)
		return (0);
	v.img = mlx_new_image(v.mlx, MAP_W, MAP_H);
	if (!v.img)
		return (0);
	v.addr = mlx_get_data_addr(v.img, &v.bpp, &v.line_len, &v.endian);
	if (!v.addr)
		return (0);
	mlx_hook(v.win, 2, 1L << 0, (void *)key_press, &v);
	mlx_hook(v.win, 17, 0, (void *)close_window, &v);
	mlx_loop_hook(v.mlx, (void *)render_frame, &v);
	mlx_loop(v.mlx);
	return (1);
}