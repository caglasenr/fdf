/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_fit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csener <csener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:02:47 by csener            #+#    #+#             */
/*   Updated: 2025/12/09 19:19:53 by csener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	updt_bds(t_point p, t_bounds *b)
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
			updt_bds(p, b);
			x++;
		}
		y++;
	}
}

void	auto_fit_and_center(t_mlx *mlx)
{
	t_bounds	bounds;
	int			map_w;
	int			map_h;
	int			zoom_x;
	int			zoom_y;

	calc_bounds(mlx, &bounds, 1);
	map_w = bounds.max_x - bounds.min_x;
	map_h = bounds.max_y - bounds.min_y;
	if (map_w == 0)
		map_w = 1;
	if (map_h == 0)
		map_h = 1;
	zoom_x = (WIN_WIDTH * 0.8) / map_w;
	zoom_y = (WIN_HEIGHT * 0.8) / map_h;
	if (zoom_x < zoom_y)
		mlx->zoom = zoom_x;
	else
		mlx->zoom = zoom_y;
	if (mlx->zoom < 1)
		mlx->zoom = 1;
	calc_bounds(mlx, &bounds, mlx->zoom);
	mlx->offset_x = (WIN_WIDTH - (bounds.max_x + bounds.min_x)) / 2;
	mlx->offset_y = (WIN_HEIGHT - (bounds.max_y + bounds.min_y)) / 2;
}
