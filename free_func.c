#include "mlx.h"
#include <stdlib.h>
#include "fdf.h"
void free_data_map(t_data *data)
{
    int i;
    if(!data)
        return ;
    if(data->map)
    {
        i=0;
        while( i <data->height)
        {
            free(data->map[i]);
            i++;
        }
        free(data->map);
        data->map = NULL;
    }
    if(data->width)
    {
        free(data->width);
        data->width = NULL;
    }
    if(data->points)
    {
        i = 0;
        while(i < data->height)
        {
            free(data->points[i]);
            i++;
        }
        
    }
    free(data->points);
    data->points = NULL;
}
int exit_program(t_mlx *mlx)
{
    free_data_map(mlx->data);
    if(mlx->win)
        mlx_destroy_window(mlx->mlx, mlx->win);
    exit(0);
    return 0;
}
void free_split(char **str)
{
    int i;
    if(str == NULL)
        return;
    i = 0;
    while(str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}
