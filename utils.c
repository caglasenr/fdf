/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csener <csener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 19:06:34 by csener            #+#    #+#             */
/*   Updated: 2025/12/09 19:08:31 by csener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stddef.h>
#include "get_next_line.h"
#include "fdf.h"
#include "mlx.h"

int	invalid_file(char *file_name)
{
	int	i;

	i = 0;
	while (file_name[i])
		i++;
	if (i < 5)
		return (0);
	if (file_name[i - 4] == '.' && file_name[i - 3] == 'f'
		&& file_name[i - 2] == 'd' && file_name[i - 1] == 'f')
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int	res;
	int	i;
	int	sign;

	res = 0;
	i = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

int	get_height(char *file_name)
{
	int		fd;
	int		height;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (1);
	height = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

int	get_width(char *line)
{
	int		width;
	char	**arr;

	width = 0;
	arr = ft_split(line, ' ');
	if (!arr)
		exit(1);
	while (arr[width])
		width++;
	free_split(arr);
	return (width);
}
