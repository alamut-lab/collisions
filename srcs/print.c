#include "../includes/collision.h"

void print_pos(t_data *d)
{
	printf(YELLOW"pos array = \n");
	for (size_t i = 0; i < N_PARTICULES; i++)
	{
		printf("id:%-3ld | x = %-3d | y = %-3d\n", i, d->pos[i].x,  d->pos[i].y);
	}
	printf("\n"RESET);
}

void    print_data(t_data *d)
{
    uint8_t     *map;
    uint32_t    i;
    uint32_t    x;
    uint32_t    y;
    int32_t     idx;

    printf("MAP_W=%d MAP_H=%d size=%d\n", MAP_W, MAP_H, MAP_W * MAP_H);
    map = calloc(MAP_W * MAP_H, sizeof(uint8_t));
    if (!map)
        return ;
    
    // fill map
    for (i = 0; i < d->n_particle; i++)
    {
        idx = d->pos[i].y * MAP_W + d->pos[i].x;
        if (map[idx] < UINT8_MAX)
            map[idx]++;
    }
    // pritn_map;
    for (y = 0; y < MAP_H; y++)
    {
        for (x = 0; x < MAP_W; x++)
        {
            idx = y * MAP_W + x;
            if (map[idx] == 0)
                map[idx] = (unsigned char)'.';
            else if (map[idx] > 9)
                map[idx] = (unsigned char)'+';
            else
                map[idx] += '0';
            write(1, &map[idx], 1);
        }
        write(1, "\n", 1);
    }
    
    free(map);
}

void    print_cells(t_data *d)
{
    uint8_t     *map;
    uint32_t    i;
    uint32_t    x;
    uint32_t    y;

    map = calloc(d->cell_count, sizeof(uint8_t));
    if (!map)
        return ;

    i = 0;
    while (i < d->cell_count)
    {
        if (d->cell_head[i] == -1)
            map[i] = '.';
        else
            map[i] = 'X';
        i++;
    }

    i = 0;
    y = 0;
    while (y < d->rows)
    {
        x = 0;
        while (x < d->cols)
        {
            write(1, &map[i], 1);
            i++;
            x++;
        }
        write(1, "\n", 1);
        y++;
    }

    free(map);
}

void print_next_array(t_data *d)
{
	size_t i;
	
	printf(RED"next array = \n");
	for (i = 0; i < N_PARTICULES; i++)
	{
		printf("%3ld ", i);
	}
	printf("\n");
	for (i = 0; i < N_PARTICULES; i++)
	{
		printf("%3d ", d->next[i]);
	}
	printf("\n"RESET);
}