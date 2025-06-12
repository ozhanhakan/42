/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_lowercase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:10:07 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/02 16:25:55 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_is_lowercase(char *str)
{
	int	i;

	i = 0;
	while (*(str + i))
	{
		if ((*(str + i) < 'a') || (*(str + i) > 'z'))
		{
			return (0);
		}
		i++;
	}
	return (1);
}
/* 
#include <stdio.h>

int	main(void)
{
	printf("%d\n", ft_str_is_lowercase(""));
	printf("%d\n", ft_str_is_lowercase("abcd"));
	printf("%d\n", ft_str_is_lowercase("Aa"));
	printf("%d\n", ft_str_is_lowercase("a123a"));
	printf("%d\n", ft_str_is_lowercase("aa"));
	return (0);
} */
