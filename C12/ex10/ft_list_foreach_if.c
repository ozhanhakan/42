/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_foreach_if.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:42:03 by hozhan            #+#    #+#             */
/*   Updated: 2025/05/13 15:28:28 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	ft_list_foreach_if(t_list *begin_list, void (*f)(void *), void
*data_ref, int (*cmp)())
{
	while (begin_list)
	{
		if ((*cmp)(begin_list->data, data_ref) == 0)
			(*f)(begin_list->data);
		begin_list = begin_list->next;
	}
}
/* 
#include <stdio.h>
#include "ft_list.h"
#include <string.h> // ft_strcmp için

// Eşleşen veriyi ekrana yazdıran fonksiyon
void print_matching(void *data)
{
	printf("Eşleşen veri: %s\n", (char *)data);
}

// Karşılaştırma fonksiyonu (strcmp gibi çalışıyor)
// int cmp_str(void *data, void *data_ref)
// {
// 	return strcmp((char *)data, (char *)data_ref);
// }
//  
int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int main()
{
	t_list elem1 = {"Hello", NULL};
	t_list elem2 = {"World", NULL};
	t_list elem3 = {"42", NULL};
	t_list elem4 = {"World", NULL}; // İkinci "World" elemanı
	
	elem1.next = &elem2;
	elem2.next = &elem3;
	elem3.next = &elem4;

	char *search_term = "World"; // "World" olan elemanları bulalım

	ft_list_foreach_if(&elem1, print_matching, search_term, ft_strcmp);

	return 0;
} */