#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "read_map.h"
#include "get_next_line.h"


t_map *read_map(char *file)
{
    int fd = open(file, O_RDONLY);
    if(fd < 0)
        return NULL;
    t_map *map = malloc(sizeof(t_map));

    
    char *line = get_next_line(fd);

    while(line)
    {
        int width = count_colums(line);
        if(width > map->width)
            map->width = width;
        map->height++;
        free(line);
        line = get_next_line(fd);
    }
    close(fd);

    map->z = malloc(sizeof(int*)*map->height);
    int i = 0;
    while(map->height > i)
    {
      map->z[i] = malloc(sizeof(int)*map->width);
      i++;
    }
    fd = open(file,O_RDONLY);
    int y = 0;
    line = get_next_line(fd);
    while(line)
    {
        char **arr = ft_split(line);
        int x = 0;
        while(arr[x])
        {
            map->z[y][x] = atoi(arr[x]);
            x++;
        }
        y++;
        free(line);
        line = get_next_line(fd);
        free(arr);
    }
    close(fd);
    return map;
}