/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_any.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:06:48 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/26 11:53:26 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_any(char **tab, int (*f)(char *))
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (f(tab[i]))
			return (1);
		i++;
	}
	return (0);
}
/* 
#include <stdio.h>

int	is_not_empty(char *str)
{
	return (str[0]);
}

int	main(void)
{
	char	*tab1[] = {"", "1", "\0", "",0};
	char	*tab2[] = {"", "1", "", "", "","","",0};
	
	printf("Test 1: %d\n", ft_any(tab1, &is_not_empty));
	printf("Test 2: %d\n", ft_any(tab2, &is_not_empty));
	return (0);
} */