/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csener <csener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 19:08:21 by csener            #+#    #+#             */
/*   Updated: 2025/12/09 19:08:37 by csener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		res = res * 16 + value;
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
	if (token[i] == '\0')
		return (0xFFFFFF);
	return (ft_hex_to_int(token + i + 3));
}
