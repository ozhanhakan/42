/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tail.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 00:40:10 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/24 15:21:48 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tail.h"

static void	read_file_loop(int fd, char *temp, t_buffer *buf)
{
	int	ret;
	int	i;

	ret = read(fd, temp, 4096);
	while (ret > 0)
	{
		i = 0;
		while (i < ret)
		{
			buf->cbuf[buf->pos] = temp[i];
			buf->pos = (buf->pos + 1) % buf->bytes;
			buf->total++;
			i++;
		}
		ret = read(fd, temp, 4096);
	}
}

static void	print_tail_buffer(t_buffer *buf)
{
	int	start;

	if (buf->total < buf->bytes)
		start = 0;
	else
		start = buf->total % buf->bytes;
	if (buf->total < buf->bytes)
		write(1, buf->cbuf, buf->total);
	else
	{
		write(1, buf->cbuf + start, buf->bytes - start);
		if (start > 0)
			write(1, buf->cbuf, start);
	}
}

int	process_file(char *filename, int bytes)
{
	t_buffer	buf;
	int			fd;
	char		temp[4096];

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ft_print_error(filename), 1);
	buf.bytes = bytes;
	buf.total = 0;
	buf.pos = 0;
	buf.cbuf = malloc(bytes);
	if (!buf.cbuf)
	{
		close(fd);
		return (1);
	}
	read_file_loop(fd, temp, &buf);
	close(fd);
	print_tail_buffer(&buf);
	free(buf.cbuf);
	return (0);
}

int	main(int argc, char **argv)
{
	int	bytes;
	int	i;

	if (argc < 3 || argv[1][0] != '-' || argv[1][1] != 'c')
	{
		ft_putstr_fd("Usage: ./ft_tail -c <bytes> <file1> [file2 ...]\n", 2);
		return (1);
	}
	bytes = ft_atoi(argv[2]);
	if (bytes < 0)
	{
		ft_putstr_fd("ft_tail: invalid byte count\n", 2);
		return (1);
	}
	i = 3;
	while (i < argc)
	{
		if (argc - 3 > 1)
			ft_putstr_fd(basename(argv[i]), 1);
		process_file(argv[i], bytes);
		i++;
	}
	return (0);
}
