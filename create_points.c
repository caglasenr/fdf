/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_points.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csener <csener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:01:21 by csener            #+#    #+#             */
/*   Updated: 2025/12/09 18:02:35 by csener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line.h"

static void	process_line(t_data *data, char *line, int y, int fd)
{
	char	**arr;
	int		x;

	arr = ft_split(line, ' ');
	if (!arr)
	{
		free(line);
		close(fd);
		exit(1);
	}
	data->points[y] = malloc(sizeof(t_point) * data->width[y]);
	if (!data->points[y])
		exit(1);
	x = 0;
	while (x < data->width[y])
	{
		data->points[y][x].x = x;
		data->points[y][x].y = y;
		data->points[y][x].z = data->map[y][x];
		data->points[y][x].color = get_color(arr[x]);
		x++;
	}
	free_split(arr);
	free(line);
}

void	create_points(t_data *data, char *file_name)
{
	int		y;
	int		fd;
	char	*line;

	y = 0;
	data->points = malloc(sizeof(t_point) * data->height);
	if (!data->points)
		exit(1);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		exit(1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		process_line(data, line, y, fd);
		y++;
		line = get_next_line(fd);
	}
	close(fd);
}
