/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csener <csener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:35:17 by csener            #+#    #+#             */
/*   Updated: 2025/12/09 18:35:41 by csener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	is_sep(char c, char sep)
{
	return (c == sep);
}

int	word_count(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c || str[i] == '\n')
			i++;
		if (str[i] != '\0')
		{
			count++;
			while (str[i] != c && str[i] != '\0' && str[i] != '\n')
				i++;
		}
	}
	return (count);
}

static char	*word_dup(const char *s, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

static void	split_helper(char *s, char **arr, char sep)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == sep || s[i] == '\n'))
			i++;
		start = i;
		while (s[i] && !is_sep(s[i], sep) && s[i] != '\n')
			i++;
		if (i > start)
			arr[j++] = word_dup(s, start, i);
	}
	arr[j] = NULL;
}

char	**ft_split(char *s, char sep)
{
	char	**arr;

	if (!s)
		return (NULL);
	arr = malloc((word_count(s, sep) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	split_helper(s, arr, sep);
	return (arr);
}
