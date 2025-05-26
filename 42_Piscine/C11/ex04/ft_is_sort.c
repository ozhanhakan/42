/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:54:08 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/27 14:44:33 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_sort(int *tab, int length, int (*f)(int, int))
{
	int	i;
	int	cmp;
	int	res;

	i = 0;
	res = 0;
	while (i < length - 1)
	{
		cmp = f(tab[i], tab[i + 1]);
		if (cmp <= 0)
			res = 1;
		else
			return (0);
		i++;
	}
	return (res);
}
/* 

int	ft_cmp(int i1, int i2)
{
	if (i1 < i2)
		return (-1);
	else if (i1 == i2)
		return (0);
	else
		return (1);
}

#include <stdio.h>

int	main(void)
{
	int	tab1[] = {1,2,3,3,4,5,6};
	int	tab2[] = {1,2,3,4,5};
	
	printf("Test 1: %d\n",
		ft_is_sort(tab1,sizeof(tab1)/sizeof(tab1[0]), &ft_cmp));
	printf("Test 2: %d\n",
		ft_is_sort(tab2,sizeof(tab2)/sizeof(tab2[0]), &ft_cmp));
	return (0);
} */