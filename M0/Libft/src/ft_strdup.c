/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:16:31 by hozhan            #+#    #+#             */
/*   Updated: 2025/06/25 17:21:40 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*copy;
	size_t	len;

	len = ft_strlen(src);
	copy = (char *)malloc(sizeof(char) * len + 1);
	if (copy == 0)
		return (NULL);
	ft_memcpy(copy, src, len);
	copy[len] = '\0';
	return (copy);
}
