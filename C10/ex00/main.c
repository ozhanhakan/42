/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:12:33 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/23 09:24:11 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 4096

void	ft_putstr(char *str)
{
	while (*str)
		write(2, str++, 1);
}

int	open_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr("Cannot read file.\n");
		return (-1);
	}
	return (fd);
}

void	read_and_print(int fd)
{
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, sizeof(buffer));
		if (bytes_read == -1)
		{
			ft_putstr("Cannot read file.\n");
			break ;
		}
		write(1, buffer, bytes_read);
	}
}

int	main(int argc, char **argv)
{
	int	fd;

	if (argc < 2)
		ft_putstr("File name missing.\n");
	else if (argc > 2)
		ft_putstr("Too many arguments.\n");
	else
	{
		fd = open_file(argv[1]);
		if (fd != -1)
		{
			read_and_print(fd);
			close(fd);
		}
		return (0);
	}
	return (1);
}
