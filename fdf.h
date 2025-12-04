#ifndef FDF_H
#define FDF_H

typedef struct s_data
{
    int *width;
    int height;
    int **map;
    //t_map map
}t_data;
int invalid_file(char *file_name);
char **ft_split(char *str, char c);
int ft_atoi(char *str);
int get_height(char *file_name);
int get_width(char *line);
void parse_map(char *file_name, t_data *data);

#endif