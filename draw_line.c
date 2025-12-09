/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csener <csener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:00:38 by csener            #+#    #+#             */
/*   Updated: 2025/12/09 18:34:23 by csener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_line_loop(t_mlx *mlx, float x, float y, t_line_data data)
{
	int	i;

	i = 0;
	while (i < data.steps)
	{
		pixel_put(mlx, (int)x, (int)y, data.color);
		x += data.x_inc;
		y += data.y_inc;
		i++;
	}
}

void	draw_line(t_mlx *mlx, t_point point_1, t_point point_2, int color)
{
	t_line_data	data;
	float		dx;
	float		dy;

	dx = point_2.x - point_1.x;
	dy = point_2.y - point_1.y;
	if (ft_fabs(dx) > ft_fabs(dy))
		data.steps = ft_fabs(dx);
	else
		data.steps = ft_fabs(dy);
	data.x_inc = dx / data.steps;
	data.y_inc = dy / data.steps;
	data.color = color;
	draw_line_loop(mlx, point_1.x, point_1.y, data);
}
