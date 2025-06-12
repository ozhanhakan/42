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
