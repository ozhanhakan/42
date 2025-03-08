#include <unistd.h>

void ft_putchar(char c)
{
	write(1, &c, 1);
}

void ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int ft_atoi(char *str)
{
	int i;
	int nbr;
	int sign;

	i = 0;
	nbr = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	while (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	while (str[i] >= '0' && str[i] <= '9')
		nbr = nbr * 10 + (str[i++] - '0');
	return (nbr * sign);
}

void    write_digits(int nb)
{
  if(nb > 10)
    write_digits(nb / 10);
  ft_putchar((nb%10)+'0');
}

void    ft_putnbr(int nb)
{
    if(nb < 0)
    {
      if (nb == -2147483648)
  			write(1, "-2147483648", 11);
    	else
    	{
            ft_putchar('-');
            nb = nb * -1;
            write_digits(nb);
      }
    }
    else
        write_digits(nb);
}

int check(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	if (ft_strlen(argv[1]) != 31)
		return (1);
	return (0);
}
/* void *get_numbers(char *str, int *target) geri dönüş pointer iptal edildi */
void get_numbers(char *str, int *target) 
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '4')
			target[j++] = ft_atoi(str + i);
		i++;
	}
}

int check_col_up(int board[4][4], int pos, int target[16])
{
	int i;
	int max;
	int visible_towers;

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

int check_row_right(int board[4][4], int pos, int target[16])
{
	int i;
	int max_size;
	int visible_towers;

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

int check_col_down(int board[4][4], int pos, int target[16])
{
	int i;
	int max;
	int visible_towers;

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

int check_row_left(int board[4][4], int pos, int target[16])
{
	int i;
	int max;
	int visible_towers;

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

int check_case(int board[4][4], int pos, int target[16])
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
