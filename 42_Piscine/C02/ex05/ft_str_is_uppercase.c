/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_uppercase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:50:46 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/02 16:55:01 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_uppercase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:10:07 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/02 16:25:55 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_is_uppercase(char *str)
{
	int	i;

	i = 0;
	while (*(str + i))
	{
		if ((*(str + i) < 'A') || (*(str + i) > 'Z'))
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
	printf("%d\n", ft_str_is_uppercase(""));
	printf("%d\n", ft_str_is_uppercase("abcd"));
	printf("%d\n", ft_str_is_uppercase("Aa"));
	printf("%d\n", ft_str_is_uppercase("AABZ"));
	printf("%d\n", ft_str_is_uppercase("a123a"));
	printf("%d\n", ft_str_is_uppercase("aa"));
	return (0);
}
 */