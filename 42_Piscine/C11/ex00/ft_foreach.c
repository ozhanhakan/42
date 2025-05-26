/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_foreach.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 01:08:59 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/26 01:23:36 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_foreach(int *tab, int length, void (*f)(int))
{
	int	i;

	i = 0;
	while (i < length)
	{
		f(tab[i]);
		i++;
	}
}
/* 
#include <stdio.h>


void	ft_foreach(int *tab, int length, void (*f)(int));

void	ft_putnbr(int nb)
{
	printf("%d\n", nb);
}

int	main(void)
{
	int	tab[] = {5, 10, 15, 20, 25};
	int	len;

	len = sizeof(tab) / sizeof(tab[0]);

	ft_foreach(tab, len, &ft_putnbr);
	return (0);
} */