/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:28:07 by hozhan            #+#    #+#             */
/*   Updated: 2025/02/23 17:46:19 by hozhan           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
//#include <stdio.h> //test library

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}
/*
test function

int	main(void)
{
	printf("%d\n", ft_strlen("Hello Norm"));
}
*/
