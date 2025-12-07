#ifndef FDF_H
#define FDF_H


typedef struct s_point
{
    int x;
    int y;
    int z;
    int color;
}t_point;

typedef struct s_data
{
    int *width;
    int height;
    int **map;
    t_point **points;
    //t_map map
}t_data;

typedef struct s_mlx
{
    void *mlx;
    void *win;
    t_data *data;
    int zoom;
    int offset_x;
    int offset_y;
} t_mlx;

int invalid_file(char *file_name);
char **ft_split(char *str, char c);
int ft_atoi(char *str);
int get_height(char *file_name);
int get_width(char *line);
void parse_map(char *file_name, t_data *data);
void draw_map(t_mlx *mlx);
void create_points(t_data *data, char *file_name);
int get_color(char *token);
#endif