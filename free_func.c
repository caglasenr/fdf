/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csener <csener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 19:59:59 by csener            #+#    #+#             */
/*   Updated: 2025/12/08 20:09:52 by csener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "fdf.h"

static void	free_map(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->height)
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
	data->map = NULL;
}

static void	free_points(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->height)
	{
		free(data->points[i]);
		i++;
	}
	free(data->points);
	data->points = NULL;
}

void	free_data_map(t_data *data)
{
	if (!data)
		return ;
	if (data->map)
		free_map(data);
	if (data->width)
	{
		free(data->width);
		data->width = NULL;
	}
	if (data->points)
		free_points(data);
}

int	exit_program(t_mlx *mlx)
{
	free_data_map(mlx->data);
	if (mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
	return (0);
}

void	free_split(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
