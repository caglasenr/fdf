#include <fcntl.h>
#include <stddef.h>
#include "get_next_line.h"
#include "fdf.h"
#include "mlx.h"
int invalid_file(char *file_name)
{
    int i = 0;
    while(file_name[i])
        i++;
    if(i<5)
        return 1;
    //a.fdf
    if(file_name[i-4] == '.' && file_name[i-3] == 'f' 
        && file_name[i-2] == 'd' && file_name[i-1] == 'f')
        return 1;
    return 0;
}
int ft_atoi(char *str)
{
    int res = 0;
    int i = 0;
    int sign = 1;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while(str[i] >= '0' && str[i] <= '9')
    {
        res = res*10 + (str[i] - '0');
        i++;
    }
    return (res*sign);
}
int get_height(char *file_name)
{
    int fd = open(file_name,O_RDONLY);
    if(fd<0)
        return 1;
    int height = 0;
    char *line;
    while((line = get_next_line(fd)) != NULL)
    {
        height++;
        free(line);
    }
    close(fd);
    return height;
}
int get_width(char *line)
{
    int width = 0;
    char **arr;
    arr = ft_split(line,' ');
    if(!arr)
        return 0;
    while(arr[width])
        width ++;
    int i = 0;
    while(arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
    return width;
}
static int ft_hex_to_int(char *str)
{
    int res;
    int i ;
    int value;
    res = 0;
    i = 0;
    if(str[i] == '0' && str[i+1] == 'x')
        i+=2;
    while(str[i])
    {
        if(str[i] >= '0' && str[i] <= '9')
            value = str[i] -'0';
        else if(str[i] >= 'a' && str[i] <= 'f')
            value = str[i] - 'a' + 10;
        else if(str[i] >= 'A' && str[i] <= 'F')
            value = str[i] - 'A' + 10;
        else
            break;
        res = res *16 + value;
        i++;
    }
    return res;
}
int get_color(char *token)
{
    int i = 0;
    while(token[i] && token[i] != ',')
        i++;
    if(token[i] == '\0')
        return 0xFFFFFF;
    return ft_hex_to_int(token + i + 3);
}
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
