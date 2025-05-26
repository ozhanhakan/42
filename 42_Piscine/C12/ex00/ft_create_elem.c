/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_elem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 21:57:49 by hozhan            #+#    #+#             */
/*   Updated: 2025/04/04 22:50:56 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

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
/* 
#include <stdio.h>

int main()
{
	t_list *element;

	element = ft_create_elem("Merhaba, Dünya!");
	if (element)
	{
		printf("Data: %s\n", (char *)element->data);
		printf("Next: %p\n", (char *)element->next);
	}
	else
	{
		printf("Element oluşturulamadı\n");
	}
	return (0);
} */