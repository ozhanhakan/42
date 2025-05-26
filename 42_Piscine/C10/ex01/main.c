/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:13:53 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/24 00:01:53 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <libgen.h>

#define BUFFER_SIZE 10

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	print_error(char *prog_name, char *file)
{
	write(2, prog_name, ft_strlen(prog_name));
	write(2, ": ", 2);
	write(2, file, ft_strlen(file));
	write(2, ": ", 2);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
}

int	open_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	return (fd);
}

void	read_and_print(int fd)
{
	ssize_t	bytes_read;
	char	buffer[BUFFER_SIZE];

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		write(1, buffer, bytes_read);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
}

int	main(int argc, char **argv)
{
	char	*prog_name;
	int		i;
	int		fd;

	prog_name = basename(argv[0]);
	if (argc < 2)
	{
		read_and_print(0);
		close(0);
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		fd = open_file(argv[i]);
		if (fd == -1)
			print_error(prog_name, argv[i]);
		else
		{
			read_and_print(fd);
			close(fd);
		}
		i++;
	}
	return (0);
}
