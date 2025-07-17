/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_handlers_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:05:41 by hozhan            #+#    #+#             */
/*   Updated: 2025/07/15 17:25:08 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

int	ft_print_hex_lower(unsigned int n)
{
	char	*str;
	int		count;

	str = ft_itoa_base(n, "0123456789abcdef");
	if (!str)
		return (-1);
	count = ft_putstr_fd(str, 1);
	free(str);
	return (count);
}

int	ft_print_hex_upper(unsigned int n)
{
	char	*str;
	int		count;

	str = ft_itoa_base(n, "0123456789ABCDEF");
	if (!str)
		return (-1);
	count = ft_putstr_fd(str, 1);
	free(str);
	return (count);
}

int	ft_print_percent(void)
{
	return (ft_putchar_fd('%', 1));
}
