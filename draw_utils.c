/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csener <csener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:57:55 by csener            #+#    #+#             */
/*   Updated: 2025/12/09 19:00:05 by csener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < 2000 && y >= 0 && y < 2000)
	{
		dst = mlx->addr + (y * mlx->line_len) + (x * (mlx->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

float	ft_fabs(float x)
{
	if (x < 0)
		return (-x);
	return (x);
}

void	iso_project(t_point *point, int zoom, int offset_x, int offset_y)
{
	float	x;
	float	y;
	float	z;
	float	iso_x;
	float	iso_y;

	x = point->x;
	y = point->y;
	z = point->z;
	iso_x = (x - y) * cos(0.523599);
	iso_y = (x + y) * sin(0.523599) - z * 0.2;
	point->x = iso_x * zoom + offset_x;
	point->y = iso_y * zoom + offset_y;
}
