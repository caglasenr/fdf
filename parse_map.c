/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csener <csener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 19:53:37 by csener            #+#    #+#             */
/*   Updated: 2025/12/08 20:11:40 by csener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "fdf.h"
#include <fcntl.h>

static int	**alloc_map(int height, int *width)
{
	int	**map;
	int	i;

	map = malloc(sizeof(int *) * height);
	if (!map)
		return (NULL);
	i = 0;
	while (i < height)
	{
		map[i] = malloc(sizeof(int) * width[i]);
		if (!map[i])
			return (NULL);
		i++;
	}
	return (map);
}

static void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static int	fill_map(char *file_name, t_data *data)
{
	int		fd;
	char	*line;
	int		y;
	char	**arr;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (1);
	y = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		arr = ft_split(line, ' ');
		if (!arr)
			return (free(line), close(fd), 1);
		fill_row(data, arr, y);
		free_split(arr);
		free(line);
		y++;
	}
	close(fd);
	return (0);
}

static void	fill_row(t_data *data, char **arr, int y)
{
	int	x;

	x = 0;
	while (arr[x])
	{
		data->map[y][x] = ft_atoi(arr[x]);
		x++;
	}
}

static void	read_widths(char *file_name, t_data *data)
{
	int		fd;
	char	*line;
	int		y;

	y = 0;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		exit(1);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return ;
		data->width[y++] = get_width(line);
		free(line);
	}
	close(fd);
}

void	parse_map(char *file_name, t_data *data)
{
	data->height = get_height(file_name);
	data->width = malloc(sizeof(int) * data->height);
	if (!data->width)
		exit(1);
	read_widths(file_name, data);
	data->map = alloc_map(data->height, data->width);
	if (!data->map)
		exit(1);
	if (fill_map(file_name, data))
		exit(1);
}
