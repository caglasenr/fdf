/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csener <csener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 19:05:42 by csener            #+#    #+#             */
/*   Updated: 2025/12/09 19:05:46 by csener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <fcntl.h>
#include <stddef.h>
#include "get_next_line.h"

static int	**alloc_map(int height, int *width)
{
	int	**map;
	int	i;

	map = malloc(sizeof(int *) * height);
	if (!map)
		exit(1);
	i = 0;
	while (i < height)
	{
		map[i] = malloc(sizeof(int) * width[i]);
		if (!map[i])
			exit(1);
		i++;
	}
	return (map);
}

static void	fill_map_line(t_data *data, char *line, int y)
{
	char	**arr;
	int		x;

	arr = ft_split(line, ' ');
	if (!arr)
		exit(1);
	x = 0;
	while (arr[x])
	{
		data->map[y][x] = ft_atoi(arr[x]);
		x++;
	}
	free_split(arr);
}

static void	fill_map(char *file_name, t_data *data)
{
	int		fd;
	char	*line;
	int		y;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		exit(1);
	y = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		fill_map_line(data, line, y);
		free(line);
		y++;
		line = get_next_line(fd);
	}
	close(fd);
}

void	parse_map(char *file_name, t_data *data)
{
	int		fd;
	char	*line;
	int		y;

	data->height = get_height(file_name);
	data->width = malloc(sizeof(int) * data->height);
	if (!data->width)
		exit(1);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		exit(1);
	y = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		data->width[y] = get_width(line);
		free(line);
		y++;
		line = get_next_line(fd);
	}
	close(fd);
	data->map = alloc_map(data->height, data->width);
	if (!data->map)
		exit(1);
	fill_map(file_name, data);
}
