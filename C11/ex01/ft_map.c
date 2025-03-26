/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 01:25:25 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/26 10:59:05 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	*ft_map(int *tab, int length, int (*f)(int))
{
	int	*new_tab;
	int	i;

	new_tab = (int *)malloc(sizeof(int) * length);
	if (!new_tab)
		return (0);
	i = 0;
	while (i < length)
	{
		new_tab[i] = f(tab[i]);
		i++;
	}
	return (new_tab);
}
/* 
int	add_two(int nb)
{
	return (nb + 2);
}

#include <stdio.h>

int	main(void)
{
	const int	tab[] = {1, 2, 3, 4, 5};
	int	length;
	int	*new_tab;
	int	i;

	length = sizeof(tab) / sizeof(tab[0]);
	new_tab = ft_map(tab, length, &add_two);
	if (!new_tab)
	{
		printf("Bellek ayırma hatası! \n");
		return (1);
	}
	i = 0;
	while (i < length)
	{
		printf("new_tab[%d] = %d\n", i, new_tab[i]);
		i++;
	}
	free(new_tab);
	return (0);
} */