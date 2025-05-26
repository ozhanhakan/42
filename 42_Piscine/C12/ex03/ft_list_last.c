/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_last.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 22:09:17 by hozhan            #+#    #+#             */
/*   Updated: 2025/04/07 23:54:47 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_list	*ft_list_last(t_list *begin_list)
{
	t_list	*last;

	if (!begin_list)
		return (0);
	last = begin_list;
	while (last->next)
		last = last->next;
	return (last);
}
/* 
#include <stdio.h>  // printf için
#include <stdlib.h> // malloc ve free için
#include "ft_list.h" // ft_list_last ve t_list için

int main()
{
	// Test 1: Boş liste
	t_list *empty_list = NULL;
	t_list	*last = ft_list_last(empty_list);
	printf("Boş listenin sonu: %s\n", last ? "Var" : "NULL"); // Beklenen: 0

	// Test 2: Tek elemanlı liste
	t_list *single_node = (t_list *)malloc(sizeof(t_list));
	single_node->data = "Tek düğüm";
	single_node->next = NULL;
	last = ft_list_last(single_node);
	printf("Tek düğüm sonu: %s\n", (char *)last->data); // Beklenen: Tek Düğüm
	free(single_node);

	// Test 3: Çoklu elemanlı liste
	t_list *node1 = (t_list *)malloc(sizeof(t_list));
	t_list *node2 = (t_list *)malloc(sizeof(t_list));
	t_list *node3 = (t_list *)malloc(sizeof(t_list));

	node1->data = "Düğüm 1";
	node1->next = node2;
	node2->data = "Düğüm 2";
	node2->next = node3;
	node3->data = "Düğüm 3";
	node3->next = NULL;
	last = ft_list_last(node1);
	printf("Çoklu düğüm sonu: %s\n", (char *)last->data); // Beklenen: Düğüm 3

	// Belleği temizle
	free(node1);
	free(node2);
	free(node3);

	return (0);
} */