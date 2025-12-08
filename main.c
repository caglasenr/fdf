/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csener <csener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 19:46:43 by csener            #+#    #+#             */
/*   Updated: 2025/12/08 19:52:12 by csener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include <unistd.h>
#include <stdlib.h>

static void	destroy_all(t_mlx *mlx)
{
	if (mlx->img)
		mlx_destroy_image(mlx->mlx, mlx->img);
	if (mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
	if (mlx->mlx)
	{
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
	}
	if (mlx->data)
		free_data_map(mlx->data);
}

static int	close_win(t_mlx *mlx)
{
	destroy_all(mlx);
	exit(0);
	return (0);
}

static int	handle_key(int keycode, t_mlx *mlx)
{
	if (keycode == 65307 || keycode == 53)
	{
		destroy_all(mlx);
		exit(0);
	}
	return (0);
}

static int	init_mlx(t_mlx *mlx, t_data *data)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (1);
	mlx->win = mlx_new_window(mlx->mlx, 1000, 800, "FDF");
	if (!mlx->win)
	{
		free_data_map(data);
		return (1);
	}
	mlx->img = mlx_new_image(mlx->mlx, 1000, 800);
	if (!mlx->img)
		return (destroy_all(mlx), 1);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp,
			&mlx->line_len, &mlx->endian);
	if (!mlx->addr)
		return (destroy_all(mlx), 1);
	return (0);
}

static void	start_render(t_mlx *mlx)
{
	auto_fit_and_center(mlx);
	draw_map(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	mlx_key_hook(mlx->win, handle_key, mlx);
	mlx_hook(mlx->win, 17, 0, close_win, mlx);
	mlx_loop(mlx->mlx);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_mlx	mlx;

	if (ac != 2)
		return (1);
	if (!invalid_file(av[1]))
		return (write(2, "Invalid file\n", 13), 1);
	parse_map(av[1], &data);
	create_points(&data, av[1]);
	if (init_mlx(&mlx, &data))
		return (1);
	mlx.data = &data;
	start_render(&mlx);
	return (0);
}
