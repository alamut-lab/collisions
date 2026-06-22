#include "../includes/collisions.h"

static inline void  resolve_collisions_scalar(t_data *d, int32_t a, int32_t b)
{
    int32_t dx;
    int32_t dy;
    int32_t lut_x;
    int32_t lut_y;
    t_lut   lut;

    dx = d->p.px[b] - d->p.px[a];
    dy = d->p.py[b] - d->p.py[a]; 

    lut_x = dx + COLLISION_DIST;
    lut_y = dy + COLLISION_DIST;

    if (lut_x < 0 || lut_x >= LUT_SIDE || lut_y < 0 || lut_y >= LUT_SIDE)
        return ;
    
    lut = g_lut_tab[lut_y][lut_x];

    d->p.px[a] -= lut.push_x;
    d->p.py[a] -= lut.push_y;
    d->p.px[b] += lut.push_x;
    d->p.py[b] += lut.push_y;

    d->p.vx[a] -= lut.imp_x;
    d->p.vy[a] -= lut.imp_y;
    d->p.vx[b] += lut.imp_x;
    d->p.vy[b] += lut.imp_y;
}

static inline void resolve_a_to_range(t_data *d, int32_t a, int32_t b_start, int32_t b_end)
{
    int32_t b;

    b = b_start;
    while (b < b_end)
    {
        resolve_collisions_scalar(d, a, b);
        b++;
    }
}

static inline void resolve_cell(t_data *d, int32_t cell_id, int32_t cell_x, int32_t cell_y)
{
    int32_t start_self;
    int32_t end_self;
    int32_t end_right;

    int32_t cell_id_south_left;
    int32_t cell_id_south_right;

    int32_t start_south;
    int32_t end_south;

    int32_t a;

    start_self = d->cell_start[cell_id];
    end_self = start_self + d->cell_count[cell_id];

    end_right = end_self;
    if (cell_x + 1 < CELL_W)
        end_right = d->cell_start[cell_id + 1] + d->cell_count[cell_id + 1];
    
    a = start_self;
    while (a < end_self)
    {
        resolve_a_to_range(d, a, a + 1, end_right);
        a++;
    }

    if (cell_y + 1 >= CELL_H)
        return ;
    
    if (cell_x == 0)
        cell_id_south_left = (cell_y + 1) * CELL_W + cell_x;
    else
        cell_id_south_left = (cell_y + 1) * CELL_W + cell_x - 1;
    
    if (cell_x + 1 >= CELL_W)
        cell_id_south_right = (cell_y + 1) * CELL_W + cell_x;
    else
        cell_id_south_right = (cell_y + 1) * CELL_W + cell_x + 1;

    start_south = d->cell_start[cell_id_south_left];
    end_south = d->cell_start[cell_id_south_right] + d->cell_count[cell_id_south_right];

    a = start_self;
    while (a < end_self)
    {
        resolve_a_to_range(d, a, start_south, end_south);
        a++;
    }
}

void    solve_collisions(t_data *d)
{
    int32_t x;
    int32_t y;
    int32_t cell_id;

    cell_id = 0;
    y = 0;
    while (y < CELL_H)
    {
        x = 0;
        while (x < CELL_W)
        {
            resolve_cell(d, cell_id, x, y);
            cell_id++;
            x++;
        }
        y++;
    }
}