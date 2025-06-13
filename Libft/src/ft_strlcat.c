/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:53:57 by hozhan            #+#    #+#             */
/*   Updated: 2025/06/13 18:08:10 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	remaining;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	remaining = size - 1 - dst_len;
	if (size <= dst_len)
		return (src_len + size);
	while(src && remaining > 0)
	{
		*(dst + dst_len) = *src++;
		dst++;
		remaining--;
	}
	*dst = '\0';
	return (dst_len + src_len);
}
