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
void free_data_map(t_data *data);

void auto_fit_and_center(t_mlx *mlx);

#endif