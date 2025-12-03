#include <stdlib.h>
#include "read_map.h"
#include <stddef.h>
#include <math.h>
#include <mlx.h>
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
t_point isometric_pro(t_point ptr)
{
    t_point new_p;
    const float angle = 0.523599;
    new_p.x = (ptr.x - ptr.y) * cos(angle);
    new_p.y = (ptr.x - ptr.y) * sin(angle) - ptr.z;

    new_p.z = ptr.z;
    new_p.color = ptr.color;
    return new_p;
}
static int ft_abs(int a)
{
    if(a<0)
        return -a;
    return a;
}
void draw_line(t_data *data, t_point *start, t_point *end)//çizgi çizme fonksiyonu
{
    //çizginin başlangıç ve bitiş noktalarını belirle
    // eksenlerdeki değişimin fak-rkın ne kadar olacağını bul
    //hangi eksende daha fazla ilerleyeceğini bul döngü kaç kez çalışmalı?
    
    int dx, dy, steps;
    float x, y, x_inc, y_inc;
    //delta
    dx = end.x - start.x;
    dy = end.y - start.y;
    //hangi eksen uzunsa o kadar step
    int steps;
    if(ft_abs(dx)>ft_abs(dy))
        steps = ft_abs(dx);
    else 
        steps = ft_abs(dy);

    x_inc = (float)dx / (float)steps; //her adımdaki artış miktarını hesapla
    y_inc = (float)dy / (float)steps;

    x = (float)start.x;
    y = (float)start.y;

    while(steps >= 0)
    {
        mlx_pixel_put(data->mlx_ptr, data->win_ptr,(int)x,(int)y,0xFFFFFF);
        x+= x_inc;
        y+=y_inc;
        steps--;
    }
}