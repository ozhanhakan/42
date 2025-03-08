
int	check_col_up(int board[4][4], int pos, int target[16])
{
	int	i;
	int	max;
	int	visible_towers;
	
	i = 0;
	max = 0;
	visible_towers = 0;
	if (pos / 4 == 3)
	{
		while (i < 4)
		{
			if (board[i][pos % 4] > max)
			{
				max = board[i][pos % 4];
				visible_towers++;
			}
			i++;
		}
		if (target[pos % 4] != visible_towers)
		return (1);
	}
	return (0);
}

int	check_col_down(int board[4][4], int pos, int target[16])
{
	int	i;
	int	max;
	int	visible_towers;
	
	i = 3;
	max = 0;
	visible_towers = 0;
	if (pos / 4 == 3)
	{
		while (i >= 0)
		{
			if (board[i][pos % 4] > max)
			{
				max = board[i][pos % 4];
				visible_towers++;
			}
			i--;
		}
		if (target[4 + pos % 4] != visible_towers)
		return (1);
	}
	return (0);
}

int	check_row_left(int board[4][4], int pos, int target[16])
{
	int	i;
	int	max;
	int	visible_towers;
	
	i = 0;
	max = 0;
	visible_towers = 0;
	if (pos % 4 == 3)
	{
		while (i < 4)
		{
			if (board[pos / 4][i] > max)
			{
				max = board[pos / 4][i];
				visible_towers++;
			}
			i++;
		}
		if (target[8 + pos / 4] != visible_towers)
		return (1);
	}
	return (0);
}

int	check_row_right(int board[4][4], int pos, int target[16])
{
	int	i;
	int	max_size;
	int	visible_towers;
	
	i = 4;
	max_size = 0;
	visible_towers = 0;
	if (pos % 4 == 3)
	{
		while (--i >= 0)
		{
			if (board[pos / 4][i] > max_size)
			{
				max_size = board[pos / 4][i];
				visible_towers++;
			}
		}
		if (target[12 + pos / 4] != visible_towers)
		return (1);
	}
	return (0);
}
