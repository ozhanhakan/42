/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 01:58:18 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/03 02:25:28 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	print_address(unsigned long addr)
{
	char		base[] = "0123456789ABCDEF";
	char		buf[16];
	int			i;

	i = 15;
	while (i >= 0)
	{
		buf[i] = base[addr % 16];
		addr /= 16;
		i--;
	}
	write(1, buf, 16);
}

static void	print_hex(unsigned char *addr, unsigned int size,
						unsigned int offset)
{
	char			base[] = "0123456789ABCDEF";
	unsigned int	i;
	unsigned char	c;

	i = 0;
	while (i < 16)
	{
		if (offset + i < size)
		{
			c = addr[offset + i];
			write(1, &base[c / 16], 1);
			write(1, &base[c % 16], 1);
		}
		else
			write(1, "  ", 2);
		if (i % 2)
			write(1, " ", 1);
		i++;
	}
}

static void	print_chars(unsigned char *addr, unsigned int size,
						  unsigned int offset)
{
	unsigned int	i;
	char	c;

	i = 0;
	while (i < 16 && offset + i < size)
	{
		c = addr[offset + i];
		if (c >= 32 && c < 127)
			write(1, &c, 1);
		else
			write(1, ".", 1);
		i++;
	}
}

void	*ft_print_memory(void *addr, unsigned int size)
{
	unsigned int	offset;
	unsigned char	*str;

	offset = 0;
	str = (unsigned char *)addr;
	while (offset < size)
	{
		print_address((unsigned long)(str + offset));
		write(1, ": ", 2);
		print_hex(str, size, offset);
		print_chars(str, size, offset);
		write(1, "\n", 1);
		offset += 16;
	}
	return (addr);
}

int	main(void)
{
	char	str[] = "Burada normal bir metin ve bazi \n \t karakterler var ";
	// char	str[] = "";
	ft_print_memory(str, sizeof(str) - 1);
	return (0);
}