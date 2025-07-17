/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:07:45 by hozhan            #+#    #+#             */
/*   Updated: 2025/07/15 16:56:35 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_putchar_fd(char c, int fd)
{
	if (write(fd, &c, 1) == -1)
		return (-1);
	return (1);
}

int	ft_putstr_fd(char *s, int fd)
{
	int	len;
	int	i;

	if (!s)
		return (-1);
	len = 0;
	i = 0;
	while (s[i])
	{
		if (ft_putchar_fd(s[i], fd) == -1)
			return (-1);
		len++;
		i++;
	}
	return (len);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}
