#include "mlx.h"
#include "read_map.h"

/*void draw_map(void *mlx, void *win, t_map *map)
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
}*/
#define ZOOM 10
#define X_OFFSET 400
#define Y_OFFSET 300
void draw_map(t_data *data)
{
    int x,y;
    t_point start,end;
    y = 0;
    while(data->map[y])
    {
        x = 0;
        while(data->map[y][x].z != -9999) //harita sonu
        {
            start = data->map[y][x];
            start.x += ZOOM;
            start.y += ZOOM;
            start.z += ZOOM / 2;
            start = isometric_pro(start);
            start.x += X_OFFSET;
            start.y += Y_OFFSET;
            //yatay çizgi sağ tarafa
            if (data->map[y][x + 1].z != -9999) 
            {
                end = data->map[y][x + 1];
                end.x *= ZOOM;
                end.y *= ZOOM;
                end.z *= ZOOM / 2;
                end = isometric_pro(end);
                end.x += X_OFFSET;
                end.y += Y_OFFSET;
                draw_line(data, &start, &end);
            }
            // 3. Dikey Çizgi Çizme (Aşağıdaki noktaya)
            if (data->map[y + 1] && data->map[y + 1][x].z != -9999)
            {
                end = data->map[y + 1][x];
                end.x *= ZOOM;
                end.y *= ZOOM;
                end.z *= ZOOM / 2;
                end = isometric_pro(end);
                end.x += X_OFFSET;
                end.y += Y_OFFSET;
                draw_line(data, &start, &end);
            }
            x++;

        }
        y++;
    }
}

