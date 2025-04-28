/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_reverse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 21:05:33 by hozhan            #+#    #+#             */
/*   Updated: 2025/04/28 23:04:10 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	ft_list_reverse(t_list **begin_list)
{
	t_list	*prev;
	t_list	*current;
	t_list	*next;

	prev = NULL;
	current = *begin_list;
	next = NULL;
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*begin_list = prev;
}
/* 
#include <stdio.h>
#include <stdlib.h>
#include "ft_list.h"

// Liste oluşturma yardımcı fonksiyonu
t_list *create_list(int size)
{
    t_list *head = NULL;
    t_list *tmp;
    
    for(int i = 0; i < size; i++)
    {
        int *num = malloc(sizeof(int));
        *num = i + 1;
        tmp = malloc(sizeof(t_list));
        tmp->data = num;
        tmp->next = head;
        head = tmp;
    }
    return head;
}

// Listeyi yazdırma
void print_list(t_list *head)
{
    while(head)
    {
        printf("%d ", *(int*)head->data);
        head = head->next;
    }
    printf("\n");
}

// Test senaryoları
void test_reverse(int size)
{
    t_list *list = create_list(size);
    
    printf("Original: ");
    print_list(list);
    
    ft_list_reverse(&list);
    
    printf("Reversed: ");
    print_list(list);
    
    // Temizlik
    t_list *tmp;
    while(list)
    {
        tmp = list->next;
        free(list->data);
        free(list);
        list = tmp;
    }
}

int main()
{
    printf("Test 1 (3 elements):\n");
    test_reverse(3);
    
    printf("\nTest 2 (1 element):\n");
    test_reverse(1);
    
    printf("\nTest 3 (empty list):\n");
    test_reverse(0);
    
    return 0;
} */