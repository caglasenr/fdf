#include "mlx.h"
#include "read_map.h"

void draw_map(void *mlx, void *win, t_map *map)
{
    for (int y = 0; y < map->height; y++)
    {
        for (int x = 0; x < map->width; x++)
        {
            int px = x * 20;
            int py = y * 20;
            int color = 0xFFFFFF;
            mlx_pixel_put(mlx, win, px, py, color);
        }
    }
}

