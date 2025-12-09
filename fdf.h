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

    void* img; //imagedan dönen görüntü işaretçisi
    char *addr; // mlx_get_data_addr den gelen piksel verisinin başlangıç adresi
    int bpp; // bit per pixel buna bak
    int line_len; // bir satırın bellekte kapladığı bayt
    int endian; // endianness bak
} t_mlx;
typedef struct s_line_data
{
    float	steps;
    float	x_inc;
    float	y_inc;
    int		color;
}	t_line_data;
typedef struct s_bounds
{
    int	min_x;
    int	max_x;
    int	min_y;
    int	max_y;
}	t_bounds;
//aouto_fit.c
void	auto_fit_and_center(t_mlx *mlx);
//create.c
void	create_points(t_data *data, char *file_name);
//draw_line
void	draw_line(t_mlx *mlx, t_point point_1, t_point point_2, int color);
//draw_map.c
void	draw_map(t_mlx *mlx);
//draw_utils.c
void	iso_project(t_point *point, int zoom, int offset_x, int offset_y);
float	ft_fabs(float x);
void	pixel_put(t_mlx *mlx, int x, int y, int color);







int invalid_file(char *file_name);
char **ft_split(char *str, char c);
int ft_atoi(char *str);
int get_height(char *file_name);
int get_width(char *line);
void parse_map(char *file_name, t_data *data);
void draw_map(t_mlx *mlx);
void create_points(t_data *data, char *file_name);
int get_color(char *token);
//FREE
void free_split(char **str);
int exit_program(t_mlx *mlx);
void free_data_map(t_data *data);
void free_data_points(t_data *data);

void auto_fit_and_center(t_mlx *mlx);
void iso_project(t_point *point, int zoom, int offset_x, int offset_y);
float ft_fabs(float x);
void pixel_put(t_mlx *mlx, int x, int y, int color);
void draw_line(t_mlx *mlx, t_point point_1, t_point point_2, int color);

#endif