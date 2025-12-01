#include <stdlib.h>
#include "read_map.h"
#include <stddef.h>
void free_map(t_map *map)
{
    if (!map)
        return;

    for (int i = 0; i < map->height; i++)
        free(map->z[i]); // her satırı free
    free(map->z);         // matrisin kendisi
    free(map);            // struct
}
char **ft_split(char *str)
{
    int i = 0;
    int j = 0;
    int k ;
    char **arr;
    arr = malloc(sizeof(char)*1000);
    while(str[i]!='\0')
    {
        while(str[i] == ' ' || str[i] == '\t')
            i++;
        if(str[i] == '\0')
            break;
        k = 0;
        arr[j] = malloc(sizeof(char)*1000);
        while((str[i] != ' ' && str[i] != '\t') && str[i])
            arr[j][k++] = str[i++];
        arr[j][k] = '\0';
        j++;
    }
    arr[j] = NULL;
    return arr;
}
int count_colums(char *line)
{
    int count = 0;
    char **split = ft_split(line);
    while(split[count])
        count++;
    free(split);
    return count;
}
