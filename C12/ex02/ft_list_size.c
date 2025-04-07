/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 21:35:52 by hozhan            #+#    #+#             */
/*   Updated: 2025/04/07 22:02:13 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

int	ft_list_size(t_list *begin_list)
{
	int		count;
	t_list	*current;

	current = begin_list;
	count = 0;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}
/* 
#include <stdio.h>  // printf için
#include <stdlib.h> // malloc ve free için
#include "ft_list.h" // ft_list_size ve t_list için

int main()
{
    // Test 1: Boş liste
    t_list *empty_list = NULL;
    printf("Boş liste boyutu: %d\n", ft_list_size(empty_list)); // Beklenen: 0

    // Test 2: Tek elemanlı liste
    t_list *single_node = (t_list *)malloc(sizeof(t_list));
    single_node->data = "Tek düğüm";
    single_node->next = NULL;
    printf("Tek düğüm boyutu: %d\n", ft_list_size(single_node)); // Beklenen: 1
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

    printf("Çoklu düğüm boyutu: %d\n", ft_list_size(node1)); // Beklenen: 3

    // Belleği temizle
    free(node1);
    free(node2);
    free(node3);

    return (0);
} */