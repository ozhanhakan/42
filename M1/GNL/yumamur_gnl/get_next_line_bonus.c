/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumamur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:46:14 by yumamur           #+#    #+#             */
/*   Updated: 2023/02/19 13:50:00 by yumamur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

t_list	*which_file(t_list *head, int fd)
{
	t_list	*curr;

	curr = head;
	if (curr->nbr == ((unsigned int)fd + 1))
		return (curr);
	while (curr->nbr)
	{
		if (!curr->next)
		{
			curr->next = malloc(sizeof(t_list)); 
			if (!curr->next)
				return (NULL);
			curr->next->content = NULL;
			curr->next->prev = curr;
			curr->next->nbr = 0;
			curr->next->next = NULL;
		}
		curr = curr->next;
		if (curr->nbr == ((unsigned int )fd) + 1)
			return (curr);
	}
	curr->nbr = ((unsigned int )fd) + 1;
	return (curr);
}

char	*get_to_second_line(char *content)
{
	char	*ret;
	int		i1;
	int		i2;

	i1 = 0;
	while (content[i1] && content[i1] != '\n')
		i1++;
	if (!content[i1] || (content[i1] == '\n' && content[i1 + 1] == '\0'))
	{
		free(content);
		return (NULL);
	}
	ret = malloc(ft_strlen(content) - i1);
	if (!ret)
	{
		free(content);
		return (NULL);
	}
	i2 = 0;
	while (content[++i1])
		ret[i2++] = content[i1];
	ret[i2] = '\0';
	free(content);
	return (ret);
}

char	*get_first_line(const char *content)
{
	int		i;
	int		end;
	char	*ret;

	i = 0;
	if (!content[i])
		return (NULL);
	while (content[i] && content[i] != '\n')
		i++;
	end = 1;
	if (content[i] == '\n')
		end++;
	ret = malloc(i + end);
	if (!ret)
		return (NULL);
	i = 0;
	while (content[i] && content[i] != '\n')
	{
		ret[i] = content[i];
		i++;
	}
	if (content[i] == '\n')
		ret[i++] = '\n';
	ret[i] = '\0';
	return (ret);
}

void	read_line(t_list *curr)
{
	char	*concat;
	int		bytes_readed;

	concat = malloc(BUFFER_SIZE + 1);
	if (!concat)
		return ;
	bytes_readed = 1;
	while (bytes_readed != 0 && !ft_strchr(curr->content, '\n'))
	{
		bytes_readed = read((curr->nbr - 1), concat, BUFFER_SIZE);
		if (bytes_readed == -1)
		{
			free(concat);
			free(curr->content);
			curr->content = NULL;
			curr->nbr = 0;
			return ;
		}
		concat[bytes_readed] = '\0';
		curr->content = ft_strjoin(curr->content, concat);
	}
	free(concat);
}

char	*get_next_line(int fd)
{
	char			*ret;
	static t_list	head;
	t_list			*curr;
	int				ctl;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	curr = which_file(&head, fd);
	read_line(curr);
	ctl = 0;
	if (curr->content == NULL)
	{
		ctl = 1;
		if (curr != &head)
			curr->prev->next = curr->next;
		if (curr->next && curr != &head)
			curr->next->prev = curr->prev;
		if (curr != &head)
		{
			free(curr);
		}
		return (NULL);
	}
	ret = get_first_line(curr->content);
	curr->content = get_to_second_line(curr->content);
	if (curr->content == NULL && curr != &head && !ctl)
	{
		if (curr->next)
		{
			curr->prev->next = curr->next;
			curr->next->prev = curr->prev;
		}
		else
			curr->prev->next = NULL;
		free(curr);
	}
	return (ret);
}
