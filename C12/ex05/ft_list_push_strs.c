/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_strs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:47:28 by hozhan            #+#    #+#             */
/*   Updated: 2025/04/16 16:04:06 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	ft_list_clear(t_list *head)
{
	t_list	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

t_list	*ft_list_push_strs(int size, char **strs)
{
	t_list	*head;
	t_list	*new_elem;
	int		i;

	head = NULL;
	i = 0;
	if (size <= 0 || !strs)
		return (NULL);
	while (i < size)
	{
		new_elem = ft_create_elem(strs[i]);
		if (!new_elem)
		{
			ft_list_clear(head);
			return (NULL);
		}
		new_elem->next = head;
		head = new_elem;
		i++;
	}
	return (head);
}
/* 
#include <stdio.h>

int main()
{
	char *strs[] = {"A", "B", "C"};
	
	// Kasıtlı olarak 4. elemanı NULL yapalım (ft_create_elem başarısız olsun)
	char *invalid_strs[] = {"X", NULL, "Z"};
	
	t_list *list1 = ft_list_push_strs(3, strs); // Başarılı
	t_list *list2 = ft_list_push_strs(3, invalid_strs); //hata verir mi?
	t_list *current = list1;
	while (current) {
		t_list *next = current->next; // Sonraki düğümü kaydet
		printf("Data: %s\n", (char *)current->data);
		free(current); // Mevcut düğümü serbest bırak
		current = next; // Sonraki düğüme geç
	}
	list1 = NULL; // Liste pointer'ını sıfırla
	current = list2;
	while (current) {
		t_list *next = current->next; // Sonraki düğümü kaydet
		printf("Data: %s\n", (char *)current->data);
		free(current); // Mevcut düğümü serbest bırak
		current = next; // Sonraki düğüme geç
	}
	list2 = NULL; // Liste pointer'ını sıfırla
	// list2 NULL olmalı ve bellek sızıntısı OLMAMALI
	ft_list_clear(list1); // Manuel temizlik (gerçek projede otomatik yapılmalı)
	list1 = NULL; // Liste pointer'ını sıfırla
	ft_list_clear(list2); 
	ft_list_clear(list1);
	return (0);
} */