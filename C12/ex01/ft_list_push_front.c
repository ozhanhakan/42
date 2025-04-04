/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_front.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 23:06:44 by hozhan            #+#    #+#             */
/*   Updated: 2025/04/04 23:34:06 by hozhan           ###   ########.fr       */
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
/* 
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

int main()
{
	t_list *list = NULL;
	
	ft_list_push_front(&list, "Birinci Eleman");
	ft_list_push_front(&list, "İkinci Eleman");
	ft_list_push_front(&list, "Üçüncü Eleman");

	t_list *temp = list;
	
	while (temp)
	{
		printf("Data: %s\n", (char *)temp->data);
		temp = temp->next;
	}
	
	return (0);
} */