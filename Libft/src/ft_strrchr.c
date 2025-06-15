/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 23:48:56 by hozhan            #+#    #+#             */
/*   Updated: 2025/06/15 22:21:39 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	size_t	i;

	ptr = (char *)s;
	i = ft_strlen(s);
	if ((char)c == '\0')
		return (ptr + i);
	while (i)
	{
		if (ptr[i - 1] == (char)c)
			return (ptr + i - 1);
		i--;
	}
	return (NULL);
}
