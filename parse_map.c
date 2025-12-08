#include <fdf.h>
#include <fcntl.h>
#include <stddef.h>
#include "get_next_line.h"
static int **alloc_map(int height, int *width)
{
    int **map = malloc(sizeof(int*)*height);
    int i = 0;
    while(i<height)
    {
        map[i] = malloc(sizeof(int)*width[i]);
        i++;
    }
    return map;
}
static void fill_map(char *file_name, t_data *data)
{
    int fd = open(file_name,O_RDONLY);
    char *line;
    int y = 0;
    
    while((line = get_next_line(fd))!=NULL)
    {
        char **arr = ft_split(line,' ');
        int x =0;
        while(arr[x])
        {
            data->map[y][x] = ft_atoi(arr[x]);
            
            x++;
        }
        int i = 0;
        while(arr[i])
        {
            free(arr[i]);
            i++;
        }
        free(arr);
        free(line);
        y++;
    }
    close(fd);
}
void parse_map(char *file_name, t_data *data)
{
    int fd;
    char *line;
    int y = 0;

    data->height = get_height(file_name);
    data->width = malloc(sizeof(int)*data->height);
    if(!data->width)
        exit(1);
    fd = open(file_name,O_RDONLY);
    while((line = get_next_line(fd)) != NULL)
    {
        data->width[y] = get_width(line);
        free(line);
        y++;
    }
    close(fd);
    data->map = alloc_map(data->height,data->width);
    fill_map(file_name,data);
    
}
