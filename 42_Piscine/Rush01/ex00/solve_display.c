/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 08:18:11 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/09 15:52:28 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strlen(char *str);
int		check_col_up(int board[4][4], int pos, int target[16]);
int		check_col_down(int board[4][4], int pos, int target[16]);
int		check_row_left(int board[4][4], int pos, int target[16]);
int		check_row_right(int board[4][4], int pos, int target[16]);

int	check(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	if (ft_strlen(argv[1]) != 31)
		return (1);
	return (0);
}

int	check_case(int board[4][4], int pos, int target[16])
{
	if (check_row_left(board, pos, target) == 1)
		return (1);
	if (check_row_right(board, pos, target) == 1)
		return (1);
	if (check_col_down(board, pos, target) == 1)
		return (1);
	if (check_col_up(board, pos, target) == 1)
		return (1);
	return (0);
}

int	check_double(int board[4][4], int pos, int size)
{
	int	i;

	i = 0;
	while (i < pos / 4)
	{
		if (board[i][pos % 4] == size)
			return (1);
		i++;
	}
	i = 0;
	while (i < pos % 4)
	{
		if (board[pos / 4][i] == size)
			return (1);
		i++;
	}
	return (0);
}

int	solve(int board[4][4], int target[16], int pos)
{
	int	size;

	if (pos == 16)
		return (1);
	size = 1;
	while (size <= 4)
	{
		if (check_double(board, pos, size) == 0)
		{
			board[pos / 4][pos % 4] = size;
			if (check_case(board, pos, target) == 0)
			{
				if (solve(board, target, pos + 1) == 1)
					return (1);
			}
			else
				board[pos / 4][pos % 4] = 0;
		}
		size++;
	}
	return (0);
}
