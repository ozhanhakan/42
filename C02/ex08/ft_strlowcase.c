/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlowcase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 21:17:37 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/02 21:20:08 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strlowcase(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] = 'a' + str[i] - 'A';
		i++;
	}
	return str;
}
/* 
#include <stdio.h>

int	main(void)
{
char	temp[] ="aBcDeFgH";
printf("%s\n", ft_strlowcase(temp));
} */