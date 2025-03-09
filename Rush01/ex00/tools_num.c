/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 08:19:20 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/09 15:13:48 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c);

int	ft_atoi(char *str)
{
	int	i;
	int	nbr;
	int	sign;

	i = 0;
	nbr = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	return (nbr * sign);
}

void	write_digits(int nb)
{
	if (nb >= 10)
		write_digits(nb / 10);
	ft_putchar((nb % 10) + '0');
}

void	ft_putnbr(int nb)
{
	if (nb < 0)
	{
		if (nb == -2147483648)
			write(1, "-2147483648", 11);
		else
		{
			ft_putchar('-');
			nb = -nb;
			write_digits(nb);
		}
	}
	else
		write_digits(nb);
}

void	get_numbers(char *str, int *target)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '4')
			target[j++] = ft_atoi(str + i);
		i++;
	}
}
