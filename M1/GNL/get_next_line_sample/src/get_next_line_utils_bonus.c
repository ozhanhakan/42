#include "../include/get_next_line_bonus.h"

int	ft_strlen(const char *str)
{
	int i = 0;
	while (str && str[i])
		i++;
	return (i);
}

t_list	*ft_lst_get_last(t_list *stash)
{
	if (!stash)
		return (NULL);
	while (stash->next)
		stash = stash->next;
	return (stash);
}

int	found_newline(t_list *stash)
{
	int i;
	if (!stash)
		return (0);
	while (stash)
	{
		i = 0;
		while (stash->content && stash->content[i])
		{
			if (stash->content[i] == '\n')
				return (1);
			i++;
		}
		stash = stash->next;
	}
	return (0);
}


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
	t_list *tmp;
	while (stash)
	{
		tmp = stash->next;
		free(stash->content);
		free(stash);
		stash = tmp;
	}
}
