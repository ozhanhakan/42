/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strs_to_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:35:20 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/20 15:15:35 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_stock_str.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strdup(char *src)
{
	int	len;
	int	i;

	len = ft_strlen(src);
	char *dest = (char *)malloc(sizeof(char)*(len + 1));
	if(!dest)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

struct s_stock_str *ft_strs_to_tab(int ac, char **av)
{
    t_stock_str *stock;
    int i;
    
	stock = (t_stock_str *)malloc(sizeof(t_stock_str)*(ac + 1));
    if(!stock)
        return (NULL);
    i = 0;
    while (i < ac)
    {
       stock[i].size = ft_strlen(av[i]);
       stock[i].str = av[i];
       stock[i].copy = ft_strdup(av[i]);
       if(!stock[i].copy)
       {
            while (i >= 0)
            {
                free(stock[i].copy);
                i--;
            }
            free(stock);
            return (NULL);
       }
       i++;
    }
    stock[i].str = 0;
    return (stock);
}


//ornek 
// Test Etme:
// Bu fonksiyonu test etmek için ft_show_tab fonksiyonunu kullanabilirsiniz. ft_show_tab fonksiyonu, t_stock_str dizisini ekrana yazdıracak şekilde tasarlanmıştır.

// Örnek bir ft_show_tab fonksiyonu:
/* 
#include <unistd.h>

void ft_putstr(char *str)
{
    while (*str)
        write(1, str++, 1);
}

void ft_putnbr(int nb)
{
    char c;
    if (nb > 9)
        ft_putnbr(nb / 10);
    c = (nb % 10) + '0';
    write(1, &c, 1);
}

void ft_show_tab(struct s_stock_str *par)
{
    int i = 0;
    while (par[i].str)
    {
        ft_putstr("String: ");
        ft_putstr(par[i].str);
        write(1, "\n", 1);

        ft_putstr("Size: ");
        ft_putnbr(par[i].size);
        write(1, "\n", 1);

        ft_putstr("Copy: ");
        ft_putstr(par[i].copy);
        write(1, "\n", 1);

        i++;
    }
} */
/* 
#include <stdio.h>
#include <stdlib.h>
//#include "ft_stock_str.h"

// ft_strs_to_tab fonksiyonunun prototipi
struct s_stock_str *ft_strs_to_tab(int ac, char **av);
 
// ft_show_tab fonksiyonunun prototipi
void ft_show_tab(struct s_stock_str *par);

int main(int argc, char **argv)
{
    // ft_strs_to_tab fonksiyonunu çağır
    t_stock_str *stock = ft_strs_to_tab(argc - 1, argv + 1);

    // Eğer bellek tahsisi başarısız olursa
    if (!stock)
    {
        printf("Bellek tahsisi başarısız!\n");
        return (1);
    }

    // ft_show_tab fonksiyonu ile sonuçları göster
    ft_show_tab(stock);

    // Belleği serbest bırak
    for (int i = 0; stock[i].str != 0; i++)
    {
        free(stock[i].copy);
    }
    free(stock);

    return (0);
} */