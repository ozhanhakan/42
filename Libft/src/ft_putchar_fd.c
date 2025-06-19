/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 23:39:06 by hozhan            #+#    #+#             */
/*   Updated: 2025/06/19 13:25:13 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/**
 * @brief Outputs a single character to the specified file descriptor.
 * @param c Character to be written
 * @param fd File descriptor for the output operation
 */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
