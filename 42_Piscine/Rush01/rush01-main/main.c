int solve(int board[4][4], int target[16], int pos)
{
	int size;

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

void display_solution(int board[4][4])
{
	int i;
	int j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			ft_putnbr(board[i][j]);
			ft_putchar(' ');
		}
		ft_putchar('\n');
	}
}

int main(int argc, char **argv)
{
	int board[4][4] = {0};
  int target[16] = {0};

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
