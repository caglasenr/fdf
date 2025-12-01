#ifndef READ_MAP_H
#define READ_MAP_H
typedef struct s_map
{
    int width;
    int height;
    int **z;
    
}t_map;
t_map *read_map(char* file);
void free_map(t_map *map);
char **ft_split(char *str);
int count_colums(char *line);
void draw_map(void *mlx, void *win, t_map *map);
#endif
