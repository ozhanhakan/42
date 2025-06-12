/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_prime.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:42:40 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/11 11:27:52 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_prime(int nb)
{
	int	i;

	if (nb < 2 || (nb != 2 && nb % 2 == 0))
		return (0);
	i = 3;
	while (i < nb / 2)
	{
		if (nb % i == 0)
			return (0);
		i += 2;
	}
	return (1);
}
/* 
#include <stdio.h>

int	main(void)
{
	int i= 100;
	while (i > -10)
	{
		printf("%d asal mi: %d\n", i, ft_is_prime(i));
		i--;
	}
} */