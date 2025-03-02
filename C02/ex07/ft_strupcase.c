/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strupcase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 20:44:38 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/02 21:07:12 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strupcase(char *str)
	{
		int	i;

		i = 0;
		while (str[i])
		{
			if (str[i] >= 'a' && str[i] <= 'z')
				str[i] = 'A' + str[i] - 'a';
			i++;
		}
		return str;
	}
/* 
#include <stdio.h>

int	main(void)
{
	char	temp[] ="aBcDeFgH";
	printf("%s\n", ft_strupcase(temp));
} */