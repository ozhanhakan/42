/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tail.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 00:39:39 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/24 15:15:02 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TAIL_H
# define FT_TAIL_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <libgen.h>

int		ft_atoi(const char *str);
void	ft_putstr_fd(char *str, int fd);
void	ft_print_error(char *filename);
int		process_file(char *filename, int bytes);

typedef struct s_buffer
{
	int		total;
	int		pos;
	int		bytes;
	char	*cbuf;
}	t_buffer;

#endif
