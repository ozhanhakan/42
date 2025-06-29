/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 16:17:06 by hozhan            #+#    #+#             */
/*   Updated: 2025/06/28 16:17:08 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/get_next_line.h"

/* Looks for a newline character in the given linked list. 
// Bağlı listedeki (stash) son düğümde '\n' karakteri var mı kontrol eder.
// Satır sonu bulunursa 1, yoksa 0 döner.
*/

int	found_newline(t_list *stash)
{
	int		i;
	t_list	*current;

	if (stash == NULL)
		return (0);
	current = ft_lst_get_last(stash);
	i = 0;
	while (current->content[i])
	{
		if (current->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

/* Returns a pointer to the last node in our stash 
// Stash'in (bağlı listenin) son düğümünü döndürür.
*/

t_list	*ft_lst_get_last(t_list *stash)
{
	t_list	*current;

	current = stash;
	while (current && current->next)
		current = current->next;
	return (current);
}

/* Calculates the number of chars in the current line, including the trailing
 * \n if there is one, and allocates memory accordingly. 
// Satırın uzunluğunu hesaplar ve line için yeterli alan ayırır.
// Satır sonu (\n) dahil edilir.
*/

void	generate_line(char **line, t_list *stash)
{
	int	i;
	int	len;

	len = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		stash = stash->next;
	}
	*line = malloc(sizeof(char) * (len + 1)); // Satır için yer ayır
}

/* Frees the entire stash. 
// Tüm stash'i (bağlı listeyi) ve içeriklerini serbest bırakır.
*/

void	free_stash(t_list *stash)
{
	t_list	*current;
	t_list	*next;

	current = stash;
	while (current)
	{
		free(current->content);
		next = current->next;
		free(current);
		current = next;
	}
}

/* Calculates the length of a string (up to the null terminator). 
// String uzunluğunu hesaplar (null-terminatöre kadar)
*/

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (*(str++))
		len++;
	return (len);
}
