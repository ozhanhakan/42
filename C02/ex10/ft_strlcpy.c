/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 22:51:43 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/03 00:33:04 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int ft_strlcpy(char *dest, char *src, unsigned int size)
{
	int	i;

	i = 0;
	while ((i < size) && dest[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (i);
}
/* 
#include <stdio.h>

int	main(void)
{
	char a[5];
	
	char b [10] = "Hello 1234";
	int c = ft_strlcpy(a,b,3);
	printf("%d\n", c);
} */