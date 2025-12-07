#include "fdf.h"
#include <math.h>
#include <stdlib.h>
#include "mlx.h"
#include "get_next_line.h"
//virgülden sonra rengi al
float ft_fabs(float x)
{
    if(x<0)
        return -x;
    return x;
}
#include <fcntl.h>

void create_points(t_data *data, char *file_name)
{
    int y = 0;
    int x;
    data->points = malloc(sizeof(t_point)*data->height);
    int fd = open(file_name,O_RDONLY);
    char *line;
    while((line = get_next_line(fd)) != NULL)
    {
        char **arr = ft_split(line,' ');
        int width = data->width[y];
        data->points[y] = malloc(sizeof(t_point)*width);
        x = 0;
        while(x<data->width[y])
        {
            data->points[y][x].x = x;
            data->points[y][x].y = y;
            data->points[y][x].z = data->map[y][x];

            data->points[y][x].color = get_color(arr[x]);
            x++;
        }
        y++;
    }
}
static void iso_project(t_point *point, int zoom, int offset_x, int offset_y)
{
    int x = point->x;
    int y = point->y;
    int z = point->z;
    point->x = (x-y)*cos(0.523599) *zoom + offset_x;
    point->y = (x+y)*sin(0.523599) * zoom - z * zoom / 2 + offset_y;

}
static void draw_line(void *mlx, void *win, t_point point_1, t_point point_2,int color)
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
        mlx_pixel_put(mlx,win,(int)x,(int)y,color);
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
                draw_line(mlx->mlx, mlx->win, p, right, p.color);
            }

            if (y + 1 < mlx->data->height && mlx->data->width[y + 1] > x )
            {
                t_point down = mlx->data->points[y + 1][x];
                iso_project(&down, mlx->zoom, mlx->offset_x, mlx->offset_y);
                draw_line(mlx->mlx, mlx->win, p, down, p.color);
            }
        }
    }
}
