/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:37:37 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/05 16:34:47 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (dest[j])
		j++;
	while (src[i] && i < nb)
	{
		dest[j + i] = src[i];
		i++;
	}
	dest[j + i] = '\0';
	return (dest);
}
/* 
#include <stdio.h>
#include <string.h>

int	main()
{
	char a[20]= "1234";
	char b[]= "567890";
	char a1[20]= "1234";
	char b1[]= "567890";
	printf("a:%s, b: %s, ft_strncat:%s\n",a, b, ft_strncat( a, b,4));
	printf("a1:%s, b1: %s, strncat:%s\n",a1, b1, strncat(a1, b1,4));
} */
