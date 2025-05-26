/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush-011.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 12:00:00 by demo              #+#    #+#             */
/*   Updated: 2025/03/08 17:43:38 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

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
		if (str[i++] == '-')
			sign *= -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
		nbr = nbr * 10 + (str[i++] - '0');
	return (nbr * sign);
}

void	write_digits(int nb)
{
	if (nb > 9)
		write_digits(nb / 10);
	ft_putchar((nb % 10) + '0');
}

void	ft_putnbr(int nb)
{
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (nb < 0)
	{
		ft_putchar('-');
		nb = -nb;
	}
	if (nb <= 9)
		ft_putchar(nb + '0');
	else
		write_digits(nb);
}

int	check(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	if (ft_strlen(argv[1]) != 31)
		return (1);
	return (0);
}

void	get_numbers(char *str, int *target)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '4')
			target[j++] = ft_atoi(str + i);
		while (str[i] && str[i] != ' ')
			i++;
		if (str[i] == ' ')
			i++;
	}
}

// Helper functions split to meet line limits
int	check_col(int board[4][4], int pos, int target[16], int mode)
{
	int	i;
	int	max;
	int	vis;

	i = (mode == 0) ? 0 : 3;
	max = 0;
	vis = 0;
	while ((mode == 0 && i < 4) || (mode == 1 && i >= 0))
	{
		if (board[i][pos % 4] > max)
		{
			max = board[i][pos % 4];
			vis++;
		}
		i += (mode == 0) ? 1 : -1;
	}
	if ((mode == 0 && target[pos % 4] != vis))
		return (1);
	if (mode == 1 && target[4 + pos % 4] != vis)
		return (1);
	return (0);
}

int	check_row(int board[4][4], int pos, int target[16], int mode)
{
	int	i;
	int	max;
	int	vis;

	i = (mode == 0) ? 0 : 3;
	max = 0;
	vis = 0;
	while ((mode == 0 && i < 4) || (mode == 1 && i >= 0))
	{
		if (board[pos / 4][i] > max)
		{
			max = board[pos / 4][i];
			vis++;
		}
		i += (mode == 0) ? 1 : -1;
	}
	if ((mode == 0 && target[8 + pos / 4] != vis))
		return (1);
	if (mode == 1 && target[12 + pos / 4] != vis)
		return (1);
	return (0);
}

int	check_case(int board[4][4], int pos, int target[16])
{
	if (check_row(board, pos, target, 0) || check_row(board, pos, target, 1))
		return (1);
	if (check_col(board, pos, target, 0) || check_col(board, pos, target, 1))
		return (1);
	return (0);
}

int	check_double(int board[4][4], int pos, int size)
{
	int	i;

	i = -1;
	while (++i < pos / 4)
		if (board[i][pos % 4] == size)
			return (1);
	i = -1;
	while (++i < pos % 4)
		if (board[pos / 4][i] == size)
			return (1);
	return (0);
}

int	solve(int board[4][4], int target[16], int pos)
{
	int	size;

	if (pos == 16)
		return (1);
	size = 0;
	while (++size <= 4)
	{
		if (!check_double(board, pos, size))
		{
			board[pos / 4][pos % 4] = size;
			if (!check_case(board, pos, target))
				if (solve(board, target, pos + 1))
					return (1);
			board[pos / 4][pos % 4] = 0;
		}
	}
	return (0);
}

void	display_board(int board[4][4])
{
	int	i;
	int	j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			ft_putnbr(board[i][j]);
			j < 3 ? ft_putchar(' ') : 0;
		}
		ft_putchar('\n');
	}
}

int	main(int argc, char **argv)
{
	int	board[4][4] = {0};
	int	target[16] = {0};

	if (check(argc, argv))
	{
		ft_putstr("Error\n");
		return (0);
	}
	get_numbers(argv[1], target);
	if (solve(board, target, 0))
		display_board(board);
	else
		ft_putstr("Error\n");
	return (0);
}