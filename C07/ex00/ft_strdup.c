/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 00:02:44 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/12 00:04:11 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(char *src)
{
	char	*copy;
	int		i;

	copy = malloc(sizeof(char) * (strlen(src) + 1)); // Doğru bellek ayırma
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		copy[i] = src[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

#include <string.h> // strlen için
#include <stdio.h>

int main()
{
	char *original = "Merhaba Dunya!";
	char *copy = ft_strdup(original);

	printf("Original: %s\n", original);
	printf("Copy: %s\n", copy);

	free(copy); // Belleği serbest bırak
	return 0;
}