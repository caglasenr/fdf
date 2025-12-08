/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csener <csener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 20:01:36 by csener            #+#    #+#             */
/*   Updated: 2025/12/08 20:32:45 by csener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

static void	pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < 1000 && y >= 0 && y < 800)
	{
		dst = mlx->addr + (y * mlx->line_len) + (x * (mlx->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

static float	ft_fabs(float x)
{
	if (x < 0)
		return (-x);
	return (x);
}

static char	**safe_split(char *line, int fd)
{
	char	**arr;

	arr = ft_split(line, ' ');
	if (!arr)
	{
		free(line);
		close(fd);
		exit(1);
	}
	return (arr);
}

static void	fill_points_row(t_data *data, char **arr, int y)
{
	int	x;

	x = 0;
	while (x < data->width[y])
	{
		data->points[y][x].x = x;
		data->points[y][x].y = y;
		data->points[y][x].z = data->map[y][x];
		data->points[y][x].color = get_color(arr[x]);
		x++;
	}
}

static void	clean_func(char **arr, char *line)
{
	free_split(arr);
	free(line);
}

void	create_points(t_data *data, char *file_name)
{
	int		fd;
	int		y;
	char	*line;
	char	**arr;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		exit(1);
	data->points = malloc(sizeof(t_point *) * data->height);
	if (!data->points)
		exit(1);
	y = 0;
	line = get_next_line(fd);
	while (line)
	{
		arr = safe_split(line, fd);
		data->points[y] = malloc(sizeof(t_point) * data->width[y]);
		if (!data->points[y])
			exit(1);
		fill_points_row(data, arr, y);
		clean_func(arr, line);
		line = get_next_line(fd);
		y++;
	}
	close(fd);
}

static void	iso_project(t_point *p, int zoom, int ox, int oy)
{
	float	x;
	float	y;
	float	z;

	x = p->x;
	y = p->y;
	z = p->z;
	p->x = (x - y) * cos(0.523599) * zoom + ox;
	p->y = ((x + y) * sin(0.523599) - z * 0.2) * zoom + oy;
}

static float	get_steps(float dx, float dy)
{
	if (ft_fabs(dx) > ft_fabs(dy))
		return (ft_fabs(dx));
	return (ft_fabs(dy));
}

static void	draw_line(t_mlx *mlx, t_point a, t_point b, int color)
{
	float	dx;
	float	dy;
	float	steps;
	float	x;
	float	y;

	dx = b.x - a.x;
	dy = b.y - a.y;
	steps = get_steps(dx, dy);
	x = a.x;
	y = a.y;
	while (steps-- >= 0)
	{
		pixel_put(mlx, (int)x, (int)y, color);
		x += dx / (steps + 1);
		y += dy / (steps + 1);
	}
}

static void	draw_connections(t_mlx *mlx, t_point point, int x, int y)
{
	t_point	right;
	t_point	down;

	if (x + 1 < mlx->data->width[y])
	{
		right = mlx->data->points[y][x + 1];
		iso_project(&right, mlx->zoom, mlx->offset_x, mlx->offset_y);
		draw_line(mlx, point, right, point.color);
	}
	if (y + 1 < mlx->data->height && mlx->data->width[y + 1] > x)
	{
		down = mlx->data->points[y + 1][x];
		iso_project(&down, mlx->zoom, mlx->offset_x, mlx->offset_y);
		draw_line(mlx, point, down, point.color);
	}
}

void	draw_map(t_mlx *mlx)
{
	int		x;
	int		y;
	t_point	point;

	y = 0;
	while (y < mlx->data->height)
	{
		x = 0;
		while (x < mlx->data->width[y])
		{
			point = mlx->data->points[y][x];
			iso_project(&point, mlx->zoom, mlx->offset_x, mlx->offset_y);
			draw_connections(mlx, point, x, y);
			x++;
		}
		y++;
	}
}

static	void	update_bounds(t_bounds *b, t_point p)
{
	if (p.x < b->min_x)
		b->min_x = p.x;
	if (p.y < b->min_y)
		b->min_y = p.y;
	if (p.x > b->max_x)
		b->max_x = p.x;
	if (p.y > b->max_y)
		b->max_y = p.y;
}

static void	calc_bounds(t_mlx *mlx, t_bounds *b, int zoom)
{
	int		x;
	int		y;
	t_point	p;

	b->min_x = 1000000;
	b->min_y = 1000000;
	b->max_x = -1000000;
	b->max_y = -1000000;
	y = 0;
	while (y < mlx->data->height)
	{
		x = 0;
		while (x < mlx->data->width[y])
		{
			p = mlx->data->points[y][x];
			iso_project(&p, zoom, 0, 0);
			update_bounds(b, p);
			x++;
		}
		y++;
	}
}

static void	calc_zoom(t_mlx *mlx, t_bounds *b)
{
	int	map_w;
	int	map_h;

	map_w = b->max_x - b->min_x;
	map_h = b->max_y - b->min_y;
	if (map_w == 0)
		map_w = 1;
	if (map_h == 0)
		map_h = 1;
	mlx->zoom = (1000 * 0.8) / map_w;
	if (mlx->zoom > (800 * 0.8) / map_h)
		mlx->zoom = (800 * 0.8) / map_h;
	if (mlx->zoom < 1)
		mlx->zoom = 1;
}

void	auto_fit_and_center(t_mlx *mlx)
{
	t_bounds	b;

	calc_bounds(mlx, &b, 1);
	calc_zoom(mlx, &b);
	calc_bounds(mlx, &b, mlx->zoom);
	mlx->offset_x = (1000 - (b.max_x + b.min_x)) / 2;
	mlx->offset_y = (800 - (b.max_y + b.min_y)) / 2;
}
