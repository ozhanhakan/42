/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_printable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 20:12:31 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/02 20:42:16 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_is_printable(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 33 || str[i] > 126)
			return (0);
		i++;
	}
	return (1);
}
/* 
#include <stdio.h>

int	main(void)
{
	printf("%d\n", ft_str_is_printable(""));
	return (0);
} */