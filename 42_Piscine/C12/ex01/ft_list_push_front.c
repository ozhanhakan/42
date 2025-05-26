/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_front.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 23:06:44 by hozhan            #+#    #+#             */
/*   Updated: 2025/04/06 18:19:04 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	ft_list_push_front(t_list **begin_list, void *data)
{
	t_list	*new_element;

	new_element = ft_create_elem(data);
	if (!new_element)
		return ;
	new_element->next = *begin_list;
	*begin_list = new_element;
}
/* //test part
#include <stdio.h>

t_list	*ft_create_elem(void *data)
{
	t_list	*new_element;

	new_element = (t_list *)malloc(sizeof(t_list));
	if (!new_element)
		return (NULL);
	new_element->data = data;
	new_element->next = NULL;
	return (new_element);
}

int main() {
	t_list *list = NULL;
	char *data1 = "1. data";
	char *data2 = "2. data";
	char *data3 = "3. data";

	// Listeye eleman ekleme (Hata kontrolü eklenebilir)
	ft_list_push_front(&list, data1);
	ft_list_push_front(&list, data2);
	ft_list_push_front(&list, data3);

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
} */