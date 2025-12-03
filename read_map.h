#ifndef READ_MAP_H
#define READ_MAP_H
typedef struct s_map
{
    int width;
    int height;
    int **z;
    
}t_map;
typedef struct s_point
{
    int x;
    int y;
    int z;
    int color;
} t_point;
typedef struct s_data
{
    void *mlx_ptr; //mlx_init() dönüş değeri
    void *win_ptr; //mlx_new_window() değeri
    t_point **map;
} t_data;
void draw_line(t_data *data, t_point *start, t_point *end);//çizgi çizme fonksiyonu
static int ft_abs(int a);
t_point isometric_pro(t_point ptr);

t_map *read_map(char* file);
void free_map(t_map *map);
char **ft_split(char *str);
int count_colums(char *line);
void draw_map(void *mlx, void *win, t_map *map);
#endif
