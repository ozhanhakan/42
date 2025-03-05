/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:37:37 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/05 17:08:22 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(char *dest, char *to_find)
{
	
}

#include <stdio.h>
#include <string.h>

int	main()
{
	char a[20]= "1234";
	char b[]= "567890";
	char a1[20]= "0123456789";
	char b1[]= "345";
	//printf("a:%s, b: %s, ft_strstr:%s\n",a, b, ft_strstr( a, b,4));
	printf("a1:%s, b1: %s, strstr:%s\n",a1, b1, strstr(a1, b1));
}
