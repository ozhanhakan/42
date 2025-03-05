/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 08:49:33 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/05 09:09:21 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i]==s2[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}
/* 
#include <stdio.h>
#include <string.h>

int	main()
{
	char a[]= "b stringi";
	char b[]= "a stringi";
	printf("a:%s, b: %s, ft_strcmp:%d\n",a, b, ft_strcmp( a, b) );

	char a1[]= "a stringi";
	char b1[]= "a stringi";
	printf("a:%s, b: %s, ft_strcmp:%d",a1, b1, strcmp(a1, b1));
} */