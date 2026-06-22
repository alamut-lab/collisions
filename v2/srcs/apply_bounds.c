#include "../includes/collisions.h"

void	apply_bounds_to_one(t_data *d, int32_t i)
{
	int32_t	px;
	int32_t	py;
	int32_t vx;
	int32_t	vy;
	int32_t	out;
	bool	changed;

	px = d->p.px[i];
	py = d->p.py[i];
	vx = d->p.vx[i];
	vy = d->p.vy[i];
	changed = false;

	if (px < R)
	{
		px = R;
		out = -((vx * 8) / 10);
		if (out <= 0)
			out = 1;
		vx = out;
		changed = true;
	}
	else if (px > MAP_W - R)
	{
		px = MAP_W - R;
		out = -((vx * 8) / 10);
		if (out >= 0)
			out = -1;
		vx = out;
		changed = true;
	}
	if (py < R)
	{
		py = R;
		out = -((vy * 8) / 10);
		if (out <= 0)
			out = 1;
		vy = out;
		changed = true;
	}
	else if (py > MAP_H - R)
	{
		py = MAP_H - R;
		out = -((vy * 8) / 10);
		if (out >= 0)
			out = -1;
		vy = out;
		changed = true;
	}
	d->p.px[i] = px;
	d->p.py[i] = py;
	d->p.vx[i] = vx;
	d->p.vy[i] = vy;
	if(changed == true)
		update_cell_id(d, i);
}

void apply_bounds_to_cell(t_data *d, int32_t cell_id)
{
	int32_t	start;
	int32_t	end;
	
	start = d->cell_start[cell_id];
	end = start + d->cell_count[cell_id];
	for (int32_t i = start; i < end; i++)
		apply_bounds_to_one(d, i);
}

void apply_bounds_to_edges(t_data *d)
{
	for (int32_t layer = 0; layer < BOUND_CHECK_EDGE; layer++)
	{
		for (int32_t x = 0; x < CELL_W; x++)
		{
			apply_bounds_to_cell(d, layer * CELL_W + x);
			apply_bounds_to_cell(d, (CELL_H - 1 - layer) * CELL_W + x);
		}
		for (int32_t y = BOUND_CHECK_EDGE; y < CELL_H - BOUND_CHECK_EDGE; y++)
		{
			apply_bounds_to_cell(d, y * CELL_W + layer);
			apply_bounds_to_cell(d, y * CELL_W + (CELL_W - 1 - layer));
		}
	}
}

void	apply_bounds_after_move(t_data *d)
{
	int16_t	px;
	int16_t	py;
	int16_t vx;
	int16_t	vy;
	int16_t	out;

	for (int32_t i = 0; i < N_PARTICLES; i++)
	{
		px = d->p.px[i];
		py = d->p.py[i];
		vx = d->p.vx[i];
		vy = d->p.vy[i];

		if (px < R)
		{
			px = R;
			out = -(vx * 8) / 10;
			if (out <= 0)
				out = 1;
			vx = out;
		}
		else if (px > MAP_W - R)
		{
			px = MAP_W - R;
			out = -(vx * 8) / 10;
			if (out >= 0)
				out = -1;
			vx = out;
		}
		if (py < R)
		{
			py = R;
			out = -(vy * 8) / 10;
			if (out <= 0)
				out = 1;
			vy = out;
		}
		else if (py > MAP_H - R)
		{
			py = MAP_H - R;
			out = -(vy * 8) / 10;
			if (out >= 0)
				out = -1;
			vy = out;
		}
		d->p.px[i] = px;
		d->p.py[i] = py;
		d->p.vx[i] = vx;
		d->p.vy[i] = vy;
		update_cell_id(d, i);
	}
}
