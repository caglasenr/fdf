/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csener <csener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:53:47 by csener            #+#    #+#             */
/*   Updated: 2025/12/09 19:00:24 by csener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "mlx.h"
#include <stdlib.h>
#include <unistd.h>
#include "fdf.h"
static int	close_win(t_mlx *mlx)
{
	if (mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
	if (mlx->img)
		mlx_destroy_image(mlx->mlx, mlx->img);
	if (mlx->mlx)
	{
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
	}
	free_data_map(mlx->data);
	exit(0);
	return (0);
}

static int	handle_key(int keycode, t_mlx *mlx)
{
	if (keycode == 65307 || keycode == 53)
	{
		if (mlx->win)
			mlx_destroy_window(mlx->mlx, mlx->win);
		if (mlx->img)
			mlx_destroy_image(mlx->mlx, mlx->img);
		if (mlx->mlx)
		{
			mlx_destroy_display(mlx->mlx);
			free(mlx->mlx);
		}
		free_data_map(mlx->data);
		exit(0);
	}
	return (0);
}
int main(int ac, char *av[])
{
	t_data data;
	t_mlx mlx;

	if (ac != 2) 
		return 1;

	if(!invalid_file(av[1]))
	{
		write(2,"Invalid file\n",13);
		return 1;
	}

	parse_map(av[1], &data);
	create_points(&data,av[1]);

	mlx.mlx = mlx_init();
	if(!mlx.mlx)
	{
		free_data_map(&data);
		return 1;
	}
	mlx.win = mlx_new_window(mlx.mlx, 2000, 1000, "FDF");
	if(!mlx.win)
	{
		free_data_map(&data);
		return 1;
	}
	mlx.img = mlx_new_image(mlx.mlx,2000,1000);
	if(!mlx.img)
	{
		mlx_destroy_display(mlx.mlx);
		free_data_map(&data);
		return 1;
	}
	mlx.addr = mlx_get_data_addr(mlx.img,&mlx.bpp,&mlx.line_len,&mlx.endian);
	if(!mlx.addr)
	{
		free_data_map(&data);
		mlx_destroy_display(mlx.mlx);
		mlx_destroy_window(mlx.mlx,mlx.win);
		mlx_destroy_image(mlx.mlx,mlx.img);
		return 1;
	}

	mlx.data = &data;

	auto_fit_and_center(&mlx);
	draw_map(&mlx);
	mlx_put_image_to_window(mlx.mlx,mlx.win,mlx.img,0,0);
	mlx_key_hook(mlx.win,handle_key,&mlx);
	mlx_hook(mlx.win,17,0,close_win,&mlx);
	mlx_loop(mlx.mlx);

	
	
	return 0;
}
