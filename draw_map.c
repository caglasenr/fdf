/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csener <csener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:28:43 by csener            #+#    #+#             */
/*   Updated: 2025/12/09 18:04:08 by csener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_horizontal(t_mlx *mlx, t_point p, int x, int y)
{
	t_point	right;

	if (x + 1 < mlx->data->width[y])
	{
		right = mlx->data->points[y][x + 1];
		iso_project(&right, mlx->zoom, mlx->offset_x, mlx->offset_y);
		draw_line(mlx, p, right, p.color);
	}
}

static void	draw_vertical(t_mlx *mlx, t_point p, int x, int y)
{
	t_point	down;

	if (y + 1 < mlx->data->height && mlx->data->width[y + 1] > x)
	{
		down = mlx->data->points[y + 1][x];
		iso_project(&down, mlx->zoom, mlx->offset_x, mlx->offset_y);
		draw_line(mlx, p, down, p.color);
	}
}

void	draw_map(t_mlx *mlx)
{
	int		x;
	int		y;
	t_point	p;

	y = 0;
	while (y < mlx->data->height)
	{
		x = 0;
		while (x < mlx->data->width[y])
		{
			p = mlx->data->points[y][x];
			iso_project(&p, mlx->zoom, mlx->offset_x, mlx->offset_y);
			draw_horizontal(mlx, p, x, y);
			draw_vertical(mlx, p, x, y);
			x++;
		}
		y++;
	}
}
