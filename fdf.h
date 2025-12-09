/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csener <csener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 19:25:05 by csener            #+#    #+#             */
/*   Updated: 2025/12/09 19:25:07 by csener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIN_WIDTH 1500
# define WIN_HEIGHT 1500

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

typedef struct s_data
{
	int			*width;
	int			height;
	int			**map;
	t_point		**points;
}	t_data;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	t_data		*data;
	int			zoom;
	int			offset_x;
	int			offset_y;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}	t_mlx;

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

void	auto_fit_and_center(t_mlx *mlx);
void	create_points(t_data *data, char *file_name);
void	draw_line(t_mlx *mlx, t_point point_1, t_point point_2, int color);
void	draw_map(t_mlx *mlx);
void	iso_project(t_point *point, int zoom, int offset_x, int offset_y);
float	ft_fabs(float x);
void	pixel_put(t_mlx *mlx, int x, int y, int color);
int		get_color(char *token);
void	free_data_map(t_data *data);
void	free_data_points(t_data *data);
int		exit_program(t_mlx *mlx);
void	free_split(char **str);
char	**ft_split(char *s, char sep);
void	parse_map(char *file_name, t_data *data);
int		get_width(char *line);
int		get_height(char *file_name);
int		ft_atoi(char *str);
int		invalid_file(char *file_name);

#endif