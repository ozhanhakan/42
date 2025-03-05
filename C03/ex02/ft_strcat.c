/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:14:11 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/05 15:36:23 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[j])
	{
		j++;
	}
	while (src[i])
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
	char b[20]= "567890";
	char a1[20]= "1234";
	char b1[20]= "567890";
	printf("a:%s, b: %s, ft_strcat:%s\n",a, b, ft_strcat( a, b));
	printf("a1:%s, b1: %s, strcat:%s\n",a1, b1, strcat(a1, b1));
} */