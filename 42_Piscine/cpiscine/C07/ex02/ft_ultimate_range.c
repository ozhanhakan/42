/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_range.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:55:41 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/12 17:53:47 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*
** ft_ultimate_range:
**   - min ile max arasındaki tam sayıları içeren bir dizi oluşturur.
**   - min dahil, max dahil değildir.
**   - Dizinin boyutunu döndürür.
**   - Hata durumunda -1 döner.
**   - Eğer min >= max ise, range NULL olur ve 0 döner.
*/

int	ft_ultimate_range(int **range, int min, int max)
{
	int	size;
	int	i;

	if (min >= max)
	{
		*range = 0;
		return (0);
	}
	size = max - min;
	*range = (int *)malloc(sizeof(int) * size);
	if (*range == 0)
		return (-1);
	i = 0;
	while (min < max)
	{
		(*range)[i] = min;
		min++;
		i++;
	}
	return (size);
}
/* 
#include <stdio.h>

int main()
{
    int min = 3;
    int max = 7;
    int *range;
    int size;

    size = ft_ultimate_range(&range, min, max);

    if (size == -1)
    {
        printf("Bellek tahsisi hatası!\n");
        return (1);
    }
    else if (size == 0)
    {
        printf("Geçersiz aralık!\n");
        return (1);
    }

    printf("Oluşturulan dizi boyutu %d : dizi: ", size);
    for (int i = 0; i < size; i++)
    {
        printf("%d ", range[i]);
    }
    printf("\n");

    free(range); // Belleği serbest bırak
    return 0;
} */