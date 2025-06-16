/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:55:47 by hozhan            #+#    #+#             */
/*   Updated: 2025/06/16 21:09:39 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // ft_strlen ve gerekirse ft_strlcpy için
#include <stdlib.h> // malloc için
#include <stddef.h> // size_t için

/*
Allocates memory (using malloc(3)) and returns a
substring from the string ’s’.
The substring starts at index ’start’ and has a
maximum length of ’len’.
*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;
	size_t	actual_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		sub = (char *)malloc(1);
		if (!sub)
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	if (len > (s_len - start))
		actual_len = s_len - start;
	else
		actual_len = len;
	sub = (char *)malloc(actual_len + 1);
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, s + start, actual_len + 1);
	return (sub);
}
