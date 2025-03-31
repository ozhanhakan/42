/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_advanced_sort_string_tab.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 01:21:34 by hozhan            #+#    #+#             */
/*   Updated: 2025/04/01 01:33:08 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tab_size(char **tab)
{
	int	ret;

	ret = 0;
	while (tab[ret])
		++ret;
	return (ret);
}

void	ft_advanced_sort_string_tab(char **tab, int (*cmp)(char *, char *))
{
	int		i;
	int		str_count;
	int		swapped;
	int		end;
	char	*temp;

	str_count = ft_tab_size(tab);
	end = str_count - 1;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = -1;
		while (++i < end)
		{
			if (cmp(tab[i], tab[i + 1]) > 0)
			{
				temp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = temp;
				swapped = 1;
			}
		}
		end--;
	}
}
/* 

//Test içindir.
#include <unistd.h>
#include <stdio.h>


//argüman içinde çağrılan örnek cmp fonksiyonu test içindir.
int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

int main(void)
{
	int i;
	char *tab[]={"c2","b1","a4","c3","b0",0};
	int size = ft_tab_size(tab);
	printf("size: %d\n", size);
	
	i = 0;
	write(1, "\nBefore sorting: \n", 18);
	while (i < size) {
	ft_putstr(tab[i]);
	write(1, ",", 1);
	i++;
	}
		
	ft_advanced_sort_string_tab(tab, &ft_strcmp);
	write(1, "\nAfter sorting: \n", 17);
	
	i = 0;
	while (i < size) {
	ft_putstr(tab[i]);
	write(1, ",", 1);
	i++;
	}

	return (0);
}
 */