/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:19:20 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/12 17:38:27 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	*ft_range(int min, int max)
{
	int	*range;
	int	i;

	if (min >= max)
		return (0);
	range = (int *)malloc(sizeof(int) * (max - min));
	if (range == 0)
		return (0);
	i = 0;
	while (min < max)
	{
		range[i] = min;
		min++;
		i++;
	}
	return (range);
}
/* 
#include <stdio.h>

int main(void)
{
	int *a = ft_range(1, 20);
	if(!a)
	{
		printf("Gecersiz Aralik");
		return (1);
	}
	int i=0;
	while (i < 11)
	{
		printf("%d, ", a[i++]);
	}
	printf("\n");
	free(a);
	return (0);
} */
