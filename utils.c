/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csener <csener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 19:57:45 by csener            #+#    #+#             */
/*   Updated: 2025/12/08 19:58:49 by csener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>

int	invalid_file(char *file_name)
{
	int	i;

	i = 0;
	while (file_name[i])
		i++;
	if (i < 4)
		return (0);
	if (file_name[i - 4] == '.'
		&& file_name[i - 3] == 'f'
		&& file_name[i - 2] == 'd'
		&& file_name[i - 1] == 'f')
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
		res = (res * 10) + (str[i] - '0');
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
		return (0);
	height = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		height++;
		free(line);
	}
	close(fd);
	return (height);
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

int	get_width(char *line)
{
	int		width;
	char	**arr;

	width = 0;
	arr = ft_split(line, ' ');
	if (!arr)
		return (0);
	while (arr[width])
		width++;
	free_split(arr);
	return (width);
}

static int	ft_hex_to_int(char *str)
{
	int	res;
	int	i;
	int	value;

	res = 0;
	i = 0;
	if (str[i] == '0' && str[i + 1] == 'x')
		i += 2;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			value = str[i] - '0';
		else if (str[i] >= 'a' && str[i] <= 'f')
			value = str[i] - 'a' + 10;
		else if (str[i] >= 'A' && str[i] <= 'F')
			value = str[i] - 'A' + 10;
		else
			break ;
		res = (res * 16) + value;
		i++;
	}
	return (res);
}

int	get_color(char *token)
{
	int	i;

	i = 0;
	while (token[i] && token[i] != ',')
		i++;
	if (!token[i])
		return (0xFFFFFF);
	return (ft_hex_to_int(token + i + 3));
}
