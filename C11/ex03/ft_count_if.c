/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_if.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 23:42:46 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/27 13:46:41 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_count_if(char **tab, int length, int (*f)(char*))
{
	int	count;

	count = 0;
	while (length--)
	{
		if (f(tab[length]))
			count++;
	}
	return (count);
}


#include <stdio.h>

int	is_not_empty(char *str)
{
	return (str[0]);
}

int	main(void)
{
	char	*tab1[] = {"", "1", ",", "",0};
	char	*tab2[] = {"", "1", "", "", "2"," ","",0};
	
	printf("Test 1: %d\n",
	 ft_count_if(tab1,sizeof(tab1)/sizeof(tab1[0]) - 1, &is_not_empty));
	printf("Test 2: %d\n",
	 ft_count_if(tab2,sizeof(tab2)/sizeof(tab2[0]) - 1, &is_not_empty));
	return (0);
}