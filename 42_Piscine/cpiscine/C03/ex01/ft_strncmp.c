/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:14:11 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/07 10:52:37 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n && s1[i] == s2[i] && s1[i])
		i++;
	if (i == n)
		return (0);
	return (s1[i] - s2[i]);
}
/* 
#include <stdio.h>
#include <string.h>

int	main()
{
	char a[]= "1";
	char b[]= "1";
	printf("a:%s, b: %s, ft_strncmp:%d\n",a, b, ft_strncmp( a, b, 3));

	char a1[]= "1";
	char b1[]= "1";
	printf("a:%s, b: %s, strncmp:%d\n",a1, b1, strncmp(a1, b1, 3));
} */