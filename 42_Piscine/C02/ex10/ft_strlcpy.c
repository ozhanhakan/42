/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 22:51:43 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/04 12:17:57 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size)
{
	unsigned int	l;
	unsigned int	i;

	i = 0;
	l = 0;
	while (src[l])
		l++;
	if (size == 0)
		return (l);
	while ((i < size - 1) && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (l);
}
/*
#include <stdio.h>

int	main(void)
{
	char a[5];
	
	char b [10] = "Hello 1234";
	int c = ft_strlcpy(a,b,4);
	printf("%d\n", c);
}
*/
