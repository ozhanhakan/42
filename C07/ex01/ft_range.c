/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 00:02:09 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/12 00:02:15 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>

int *ft_range(int min, int max)
{
    int *range;
    int i;

    if (min >= max)
        return (NULL);

    range = malloc(sizeof(int) * (max - min));
    if (range == NULL)
        return (NULL);

    i = 0;
    while (min < max)
    {
        range[i] = min;
        min++;
        i++;
    }

    return (range);
}

#include <stdio.h>

int main()
{
    int min = 3;
    int max = 7;
    int *range = ft_range(min, max);

    if (range == NULL)
    {
        printf("Geçersiz aralık!\n");
        return (1);
    }

    printf("Oluşturulan dizi: ");
    for (int i = 0; i < max - min; i++)
    {
        printf("%d ", range[i]);
    }
    printf("\n");

    free(range); // Belleği serbest bırak
    return 0;
}