/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:37:37 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/06 16:54:09 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	if (to_find[i] == '\0')
		return (str);
	while (str[i])
	{
		j = 0;
		while (str[i + j] && to_find[j] && to_find[j] == str[i + j])
			j++;
		if (to_find[j] == '\0')
			return ((char *)&str[i]);
		i++;
	}
	return (0);
}
/* 
#include <stdio.h>
#include <string.h>

int	main()
{
	char a[20]= "01263456789";
	char b[]= "";
	char a1[20]= "01263456789";
	char b1[]= "";
	printf("a:%s, b: %s, ft_strstr:%s\n",a, b, ft_strstr( a, b));
	printf("a1:%s, b1: %s, strstr:%s\n",a1, b1, strstr(a1, b1));
}
 */