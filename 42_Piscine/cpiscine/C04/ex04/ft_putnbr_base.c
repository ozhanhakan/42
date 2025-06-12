/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:16:53 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/10 13:46:40 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr_base_rec(long nbr, char *base, int size)
{
	unsigned char	a;
	unsigned long	n;

	if (nbr < 0)
	{
		write(1, "-", 1);
		n = -nbr;
	}
	else
		n = nbr;
	if (n >= (unsigned long)size)
		ft_putnbr_base_rec(n / size, base, size);
	a = base[n % size];
	write(1, &a, 1);
}

int	is_valid_base(char *base)
{
	int	i;
	int	j;

	i = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		j = i + 1;
		while (base[j])
			if (base[i] == base[j++])
				return (0);
		i++;
	}
	return (i > 1);
}

void	ft_putnbr_base(int nbr, char *base)
{
	int	s;

	s = 0;
	if (is_valid_base(base))
	{
		while (base[s])
			s++;
		ft_putnbr_base_rec(nbr, base, s);
	}
}
/* 
#include <stdio.h>

void test(int nbr, char *base, char *expected_output)
{
    printf("Test: ft_putnbr_base(%d, \"%s\")\n", nbr, base);
    printf("Beklenen Çıktı: %s\n", expected_output);
    printf("Alınan Çıktı:    ");
    
    // Buffer boşaltılıyor, böylece `write(1, ...);` ile karışmaz
    fflush(stdout);

    ft_putnbr_base(nbr, base);
    
    printf("\n---------------------------------\n");
}

int main()
{
    test(42, "0123456789", "42");       // Onluk sistem (Decimal)
    test(42, "01", "101010");           // İkilik sistem (Binary)
    test(255, "0123456789ABCDEF", "FF"); // Onaltılık sistem (Hexadecimal)
    test(-42, "0123456789", "-42");      // Negatif sayı, onluk sistem
    test(42, "poneyvif", "vn");           // Base 8 (Özel karakterlerle)
    
    test(42, "0", "");                  // Tek karakter (Geçersiz)
    test(42, "0123+", "");               // '+' içeriyor (Geçersiz)
    test(42, "012301", "");              // Aynı karakter var (Geçersiz)

    return 0;
} */