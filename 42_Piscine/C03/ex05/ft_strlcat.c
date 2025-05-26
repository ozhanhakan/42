/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:06:27 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/07 10:36:30 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_len(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	dest_len;
	unsigned int	src_len;
	unsigned int	i;

	i = 0;
	dest_len = ft_len(dest);
	src_len = ft_len(src);
	if (size <= dest_len)
		return (size + src_len);
	while (src[i] && (dest_len + i + 1) < size)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}
/* 
#include <stdio.h>
#include <string.h>

int	main()
{
	char a[20]= "1234";
	char b[20]= "567890";
	//char a1[20]= "1234";
	//char b1[20]= "567890";
	printf("a:%s, b: %s,\n",a, b);
	printf("a:%s, b: %s, ft_strlcat:%u\n",a, b, ft_strlcat( a, b,11));
	//printf("a1:%s, b1: %s, strlcat:%u\n",a1, b1, strlcat(a1, b1,11));
} */