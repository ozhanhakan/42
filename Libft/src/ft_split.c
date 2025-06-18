/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:00:38 by hozhan            #+#    #+#             */
/*   Updated: 2025/06/18 12:31:34 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include "libft.h"

static size_t	ft_count_words(char const *s, char c)
{
	size_t	i;
	size_t	words;

	words = 0;
	i = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		words++;
		while (s[i] && s[i] != c)
			i++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (words);
}

static void	ft_free_all(char **arr, size_t count)
{
	while (count--)
		free(arr[count]);
	free(arr);
}

static int	ft_fill_words(char const *s, char c, char **res, size_t wc)
{
	size_t	i;
	size_t	start;
	size_t	end;

	i = -1;
	start = 0;
	while (++i < wc)
	{
		while (s[start] && s[start] == c)
			start++;
		end = start;
		while (s[end] && s[end] != c)
			end++;
		res[i] = ft_substr(s, start, end - start);
		if (!res[i])
			return (ft_free_all(res, i), 1);
		start = end;
	}
	res[i] = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	word_count;

	if (!s)
		return (NULL);
	word_count = ft_count_words(s, c);
	result = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	if (ft_fill_words(s, c, result, word_count))
		return (NULL);
	return (result);
}
