/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_alpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:09:42 by hozhan            #+#    #+#             */
/*   Updated: 2025/02/27 15:09:24 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_is_alpha(char *str)
{
	int	i;

	i = 0;
	while (*(str + i))
	{
		if (((*(str + i) < 'A') || (*(str + i) > 'Z'))
			&& ((*(str + i) < 'a') || (*(str + i) > 'z')))
		{
			return (0);
		}
		i++;
	}
	return (1);
}
/*
#include <stdio.h>
int main()
{
	//char str[] = "Hello";
	//printf("%d\n", ft_str_is_alpha(str));
	printf("%d\n", ft_str_is_alpha(""));
	printf("%d\n", ft_str_is_alpha("123a"));
	printf("%d\n", ft_str_is_alpha("Aa"));
	printf("%d\n", ft_str_is_alpha(""));
	return 0;
}
*/
