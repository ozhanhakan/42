/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 21:58:06 by hozhan            #+#    #+#             */
/*   Updated: 2025/06/28 21:58:31 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (0);
}

char	*ft_strdup(const char *s1)
{
	char	*dst;
	size_t	i;
	size_t	len;

	len = 0;
	while (s1[len])
		len++;
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = 0;
	while (s[s_len])
		s_len++;
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*ft_strjoin_and_free(char *stash, char *buffer)
{
	char	*new_str;
	int		i;
	int		j;
	int		stash_len;
	int		buffer_len;

	if (!stash)
		stash = ft_strdup("");
	stash_len = 0;
	while (stash[stash_len])
		stash_len++;
	buffer_len = 0;
	while (buffer[buffer_len])
		buffer_len++;
	new_str = (char *)malloc(sizeof(char) * (stash_len + buffer_len + 1));
	if (!new_str)
		return (free(stash), NULL);
	i = -1;
	while (++i < stash_len)
		new_str[i] = stash[i];
	j = -1;
	while (++j < buffer_len)
		new_str[i + j] = buffer[j];
	new_str[i + j] = '\0';
	free(stash);
	return (new_str);
}