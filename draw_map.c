#include "fdf.h"
#include <math.h>
#include <stdlib.h>
#include "mlx.h"
#include "get_next_line.h"
#include <fcntl.h>

//virgülden sonra rengi al

static void pixel_put(t_mlx *mlx, int x, int y, int color)
{
    char *dst;
    if(x >= 0 && x < 1000 && y>= 0 && y < 800)
    {
        dst = mlx->addr + (y * mlx->line_len) + (x * (mlx->bpp / 8));
        *(unsigned int*)dst = color;
    }
}
static float ft_fabs(float x)
{
    if(x<0)
        return -x;
    return x;
}
void create_points(t_data *data, char *file_name)
{
    int y = 0;
    int x;
    data->points = malloc(sizeof(t_point)*data->height);
    if(!data->points)
        exit(1);
    int fd = open(file_name,O_RDONLY);
    if(fd<0)
        exit(1);
    char *line;
    while((line = get_next_line(fd)) != NULL)
    {
        char **arr = ft_split(line,' ');
        if(!arr)
        {
            free(line);
            close(fd);
            exit(1);

        }
        int width = data->width[y];
        data->points[y] = malloc(sizeof(t_point)*width);
        if(!data->points[y])
            exit(1);
        x = 0;
        while(x<data->width[y])
        {
            data->points[y][x].x = x;
            data->points[y][x].y = y;
            data->points[y][x].z = data->map[y][x];

            data->points[y][x].color = get_color(arr[x]);
            x++;
        }
        free_split(arr);
        free(line);
        y++;
    }
    close(fd);
}
static void iso_project(t_point *point, int zoom, int offset_x, int offset_y)
{
    float x = point->x;
    float y = point->y;
    float z = point->z;
    
    float iso_x = (x - y) * cos(0.523599);
    float iso_y = (x + y) * sin(0.523599) - z * 0.2;  // Z'yi azalt (0.2 ile çarp)

    point->x = iso_x * zoom + offset_x;
    point->y = iso_y * zoom + offset_y;
}
static void draw_line(t_mlx *mlx,t_point point_1, t_point point_2,int color)
{
    float dx = point_2.x - point_1.x;
    float dy = point_2.y - point_1.y;

    float steps;
    if(ft_fabs(dx)>ft_fabs(dy))
        steps = ft_fabs(dx);
    else
        steps = ft_fabs(dy);
        
    float x_inc = dx /steps;
    float y_inc = dy /steps;
    float x = point_1.x;
    float y = point_1.y;
    int i = 0;
    while(i<steps)
    {
        pixel_put(mlx,(int)x,(int)y,color);
        x += x_inc;
        y += y_inc;
        i++;
    }

}
void draw_map(t_mlx *mlx)
{
    for (int y = 0; y < mlx->data->height; y++)
    {
        for (int x = 0; x < mlx->data->width[y]; x++)
        {
            t_point p = mlx->data->points[y][x];
            iso_project(&p, mlx->zoom, mlx->offset_x, mlx->offset_y);

            if (x + 1 < mlx->data->width[y])
            {
                t_point right = mlx->data->points[y][x + 1];
                iso_project(&right, mlx->zoom, mlx->offset_x, mlx->offset_y);
                draw_line(mlx, p, right, p.color);
            }

            if (y + 1 < mlx->data->height && mlx->data->width[y + 1] > x )
            {
                t_point down = mlx->data->points[y + 1][x];
                iso_project(&down, mlx->zoom, mlx->offset_x, mlx->offset_y);
                draw_line(mlx, p, down, p.color);
            }
        }
    }
}
static void calc_bounds(t_mlx *mlx, int *min_x, int *max_x, int *min_y, int *max_y,int zoom)
{
    int x, y;
    t_point p;

    *min_x = 1000000;
    *min_y = 1000000;
    *max_x = -1000000;
    *max_y = -1000000;

    y = 0;
    while (y < mlx->data->height)
    {
        x = 0;
        while (x < mlx->data->width[y])
        {
            p = mlx->data->points[y][x];
            iso_project(&p, zoom, 0, 0);

            if (p.x < *min_x) *min_x = p.x;
            if (p.y < *min_y) *min_y = p.y;
            if (p.x > *max_x) *max_x = p.x;
            if (p.y > *max_y) *max_y = p.y;
            x++;
        }
        y++;
    }
}
void auto_fit_and_center(t_mlx *mlx)
{
    int min_x, max_x, min_y, max_y;
    int map_w, map_h;
    int win_w = 1000;
    int win_h = 800;

    // 1. Önce zoom=1 ile haritanın boyutunu hesapla
    calc_bounds(mlx, &min_x, &max_x, &min_y, &max_y,1);

    map_w = max_x - min_x;
    map_h = max_y - min_y;

    if (map_w == 0) map_w = 1;
    if (map_h == 0) map_h = 1;

    // 2. Ekrana sığması için zoom hesapla
    int zoom_x = (win_w * 0.8) / map_w; // %80 kullan
    int zoom_y = (win_h * 0.8) / map_h;

    if(zoom_x < zoom_y)
        mlx->zoom =zoom_x;
    else
        mlx->zoom = zoom_y;
        
    if (mlx->zoom < 1)
        mlx->zoom = 1;

    // 3. Yeni zoom ile tekrar sınırları hesapla
    calc_bounds(mlx, &min_x, &max_x, &min_y, &max_y,mlx->zoom);

    // 4. Ortala
    mlx->offset_x = (win_w - (max_x + min_x)) / 2;
    mlx->offset_y = (win_h - (max_y + min_y)) / 2;
}