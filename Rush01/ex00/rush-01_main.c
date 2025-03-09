/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush-01_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 17:48:23 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/09 08:59:32 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putstr(char *str);
void	get_numbers(char *str, int *target);
void	display_solution(int board[4][4]);
int		solve(int board[4][4], int target[16], int pos);
int		check(int argc, char **argv);

void	reset_board(int str[4][4], int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
			str[i][j++] = 0;
		i++;
	}
}

int	main(int argc, char **argv)
{
	int	board[4][4];
	int	target[16];
	int	i;

	i = 0;
	reset_board(board, 4);
	i = 0;
	while (i < 16)
		target[i++] = 0;
	if (check(argc, argv) == 1)
	{
		ft_putstr("Error\n");
		return (0);
	}
	get_numbers(argv[1], target);
	if (solve(board, target, 0) == 1)
		display_solution(board);
	else
		ft_putstr("Error\n");
	return (0);
}
