/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexdump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:06:00 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/25 23:15:28 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define BUF_SIZE 16

void	print_offset(int offset)
{
	char	hex[9];
	int		i;

	i = 8;
	hex[8] = '\0';
	while (i-- > 0)
	{
		hex[i] = "0123456789abcdef"[offset % 16];
		offset /= 16;
	}
	write(1, hex, 8);
	write(1, "  ", 2);
}

void	print_hex_data(unsigned char *buf, int bytes_read)
{
	int		i;
	char	out[2];

	i = 0;
	while (i < bytes_read)
	{
		out[0] = "0123456789abcdef"[buf[i] / 16];
		out[1] = "0123456789abcdef"[buf[i] % 16];
		write(1, out, 2);
		write(1, " ", 1);
		if ((i + 1) % 8 == 0)
			write(1, " ", 1);
		i++;
	}
	while (i < BUF_SIZE)
	{
		write(1, "   ", 3);
		if ((i + 1) % 8 == 0)
			write(1, " ", 1);
		i++;
	}
}

void	print_ascii_data(unsigned char *buf, int bytes_read)
{
	int	i;

	i = 0;
	write(1, "|", 2);
	while (i < bytes_read)
	{
		if (buf[i] >= 32 && buf[i] <= 126)
			write(1, &buf[i], 1);
		else
			write(1, ".", 1);
		i++;
	}
	write(1, "|\n", 2);
}

void	hexdump(int fd)
{
	unsigned char	buf[BUF_SIZE];
	int				bytes_read;
	int				offset;

	offset = 0;
	bytes_read = read(fd, buf, BUF_SIZE);
	while (bytes_read > 0)
	{
		print_offset(offset);
		print_hex_data(buf, bytes_read);
		print_ascii_data(buf, bytes_read);
		offset += bytes_read;
		bytes_read = read(fd, buf, BUF_SIZE);
	}
	print_offset(offset);
	write(1, "\n", 1);
}

int	main(int argc, char **argv)
{
	int		fd;
	int		i;
	char	*str;

	if (argc != 2)
	{
		write(1, "Usage: ./ft_hexdump <file>\n", 27);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		str = strerror(errno);
		i = 0;
		while (str[i])
			i++;
		write(1, str, i);
		return (1);
	}
	hexdump(fd);
	close(fd);
	return (0);
}
