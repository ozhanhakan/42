/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:10:33 by hozhan            #+#    #+#             */
/*   Updated: 2025/04/15 18:43:55 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	ft_list_push_back(t_list **begin_list, void *data)
{
	t_list	*new_element;
	t_list	*last_element;

	new_element = ft_create_elem(data);
	if (!new_element)
		return ;
	if (!*begin_list)
	{
		*begin_list = new_element;
		return ;
	}
	last_element = *begin_list;
	while (last_element->next)
		last_element = last_element->next;
	last_element->next = new_element;
}
/*  //test part
#include <stdio.h>

int main() {
	t_list *list = NULL;
	char *data1 = "1. data";
	char *data2 = "2. data";
	char *data3 = "3. data";

	// Listeye eleman ekleme (Hata kontrolü eklenebilir)
	ft_list_push_back(&list, data1);
	ft_list_push_back(&list, data2);
	ft_list_push_back(&list, data3);

	// Listeyi yazdırma ve belleği temizleme
	t_list *current = list;
	while (current) {
		t_list *next = current->next; // Sonraki düğümü kaydet
		printf("Data: %s\n", (char *)current->data);
		free(current); // Mevcut düğümü serbest bırak
		current = next; // Sonraki düğüme geç
	}
	list = NULL; // Liste pointer'ını sıfırla

	return 0;
}  */