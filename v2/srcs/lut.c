#include "../includes/collisions.h"

t_lut	g_lut_tab[LUT_SIDE][LUT_SIDE];

/*
    init look up table
    to precalculate all possible data necessary to compute the collisions
*/
void    init_lut(void)
{
    int32_t     dx;
    int32_t     dy;
    int32_t     dist2;
    float       dist;
    float       nx;
    float       ny;
    float       overlap;
    float       penetration_vec_x;
    float       penetration_vec_y;
    t_lut       *lut;

    dy = -COLLISION_DIST;
    while (dy <= COLLISION_DIST)
    {
        // printf("test 1\n");
        dx = -COLLISION_DIST;
        while (dx <= COLLISION_DIST)
        {
            // printf("test 2\n");
            lut = &g_lut_tab[dy + COLLISION_DIST][dx + COLLISION_DIST];
            memset(lut, 0, sizeof(t_lut));

            dist2 = dx * dx + dy * dy;
            if (dist2 >= COLLISION_DIST2)
            {
                dx++;
                continue ;
            }
            nx = 1.0;
            ny = 0.0;
            dist = 0.0;
            if (dist2 != 0)
            {
                dist = sqrtf((float)dist2);
                nx = (float)dx / dist;
                ny = (float)dy / dist;
            }

            overlap = (float)COLLISION_DIST - dist;
            if (overlap <= 0.0)
            {
                dx++;
                continue ;
            }
            penetration_vec_x = overlap * nx;
            penetration_vec_y = overlap * ny;

            // calculate what we add to the psoitions
            lut->push_x = (int8_t)roundf(penetration_vec_x * 0.5);
            lut->push_y = (int8_t)roundf(penetration_vec_y * 0.5);

            if (lut->push_x == 0 && lut->push_y == 0)
            {
                if (dx == 0 && dy == 0)
                    lut->push_x = 1;
                else if (dx * dx >= dy * dy)
                    lut->push_x = sign_i32(dx);
                else
                    lut->push_y = sign_i32(dy);
            }

            // calculate what we add to the velocities
            lut->imp_x = (int8_t)roundf(penetration_vec_x);
            lut->imp_y = (int8_t)roundf(penetration_vec_y);

            dx++;
        }
        dy++;
    }
}