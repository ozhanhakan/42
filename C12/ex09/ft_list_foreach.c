/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_foreach.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:56:09 by hozhan            #+#    #+#             */
/*   Updated: 2025/05/10 16:41:26 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include <stdio.h>
/*this is allowed comment place*/

void	ft_list_foreach(t_list *begin_list, void (*f)(void *))
{
	while (begin_list)
	{
		(*f)(begin_list->data);
		begin_list = begin_list->next;
	}
}
/* 
void print_data(void *data)
{
	printf("%s\n", (char *)data);
}

void to_uppercase(void *data)
{
	char *str = (char *)data;
	while (*str)
	{
		if (*str >= 'a' && *str <= 'z')
			*str -= 32; // Küçük harfi büyük harfe çevir
		str++;
	}
}

int main()
{
	char str1[] = "hello";
	char str2[] = "world";
	char str3[] = "test";

	t_list elem1 = {str1, NULL};
	t_list elem2 = {str2, NULL};
	t_list elem3 = {str3, NULL};

	elem1.next = &elem2;
	elem2.next = &elem3;

	ft_list_foreach(&elem1, to_uppercase);
	ft_list_foreach(&elem1, print_data); // "HELLO", "WORLD", "TEST" yazdırmalı

	return 0;
}
 */