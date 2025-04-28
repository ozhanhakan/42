/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_at.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:30:40 by hozhan            #+#    #+#             */
/*   Updated: 2025/04/28 18:55:41 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_list	*ft_list_at(t_list *begin_list, unsigned int nbr)
{
	t_list	*current;

	current = begin_list;
	if (!begin_list)
		return (NULL);
	if (nbr == 0)
		return (begin_list);
	while (current != NULL && nbr > 0)
	{
		current = current->next;
		nbr--;
	}
	return (current);
}
/* 
#include <stdio.h>
#include <stdlib.h>
#include "ft_list.h"

// ft_list_at fonksiyonunuz burada veya ayrı bir dosyada olmalı

// Test için yardımcı fonksiyon: string data ile liste oluşturur
t_list *create_sample_list()
{
    t_list *node1 = malloc(sizeof(t_list));
    t_list *node2 = malloc(sizeof(t_list));
    t_list *node3 = malloc(sizeof(t_list));
    
    node1->data = "Node 1";
    node1->next = node2;
    
    node2->data = "Node 2";
    node2->next = node3;
    
    node3->data = "Node 3";
    node3->next = NULL;
    
    return node1;
}

// Test durumlarını çalıştır
void test_cases(t_list *list)
{
    printf("Test 0 (nbr=0): %s\n", (char*)ft_list_at(list, 0)->data);
    printf("Test 1 (nbr=1): %s\n", (char*)ft_list_at(list, 1)->data);
    printf("Test 2 (nbr=2): %s\n", (char*)ft_list_at(list, 2)->data);
    
    // Hata durumları
    printf("Test 3 (nbr=3): %s\n", ft_list_at(list, 3) ? "VAR" : "NULL");
    printf("Test NULL list: %s\n", ft_list_at(NULL, 0) ? "VAR" : "NULL");
    printf("(nbr=999): %s\n", ft_list_at(list, 999) ? "VAR" : "NULL");
}

int main()
{
    t_list *list = create_sample_list();
    
    test_cases(list);
    return 0;
} */