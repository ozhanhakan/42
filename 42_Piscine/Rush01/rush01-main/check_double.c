int check_double(int board[4][4], int pos, int size)
{
	int i;

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

/* can be optimized by using 	while (i < pos/4) & 	while (i < pos%4) */
