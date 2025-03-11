/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 00:27:21 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/12 00:46:09 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	get_total_length(int size, char **strs, char *sep)
{
	int	total_len;
	int	i;

	total_len = 0;
	i = 0;
	while (i < size)
	{
		total_len += ft_strlen(strs[i]);
		i++;
	}
	total_len += (size - 1) * ft_strlen(sep);
	return (total_len);
}

void	copy_strings(char *dest, int size, char **strs, char *sep)
{
	int		i;
	char	*current;

	current = dest;
	i = 0;
	while (i < size)
	{
		while (*strs[i])
			*current++ = *strs[i]++;
		if (i < size - 1)
		{
			while (*sep)
				*current++ = *sep++;
		}
		i++;
	}
	*current = '\0';
}

char	*ft_strjoin(int size, char **strs, char *sep)
{
	char	*result;
	int		total_len;

	if (size == 0)
	{
		result = (char *)malloc(1);
		if (result)
			*result = '\0';
		return (result);
	}
	total_len = get_total_length(size, strs, sep);
	result = (char *)malloc(total_len + 1);
	if (!result)
		return (NULL);
	copy_strings(result, size, strs, sep);
	return (result);
}


#include <stdio.h>

int main()
{
    char *strs[] = {"Merhaba", "42", "Okulları"};
    char *sep = " ";
    char *result;

    result = ft_strjoin(3, strs, sep);
    printf("Birleştirilmiş String: %s\n", result);

    free(result); // Belleği serbest bırak
    return 0;
}