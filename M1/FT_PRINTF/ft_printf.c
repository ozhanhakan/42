/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:47:39 by hozhan            #+#    #+#             */
/*   Updated: 2025/07/15 19:00:28 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	if (!format)
		return (-1);
	count = 0;
	va_start(args, format);
	count = ft_parse_format(format, args);
	va_end(args);
	return (count);
}

int	ft_handle_specifier(char specifier, va_list args)
{
	if (specifier == 'c')
		return (ft_print_char(va_arg(args, int)));
	else if (specifier == 's')
		return (ft_print_string(va_arg(args, char *)));
	else if (specifier == 'p')
		return (ft_print_pointer(va_arg(args, void *)));
	else if (specifier == 'd' || specifier == 'i')
		return (ft_print_decimal(va_arg(args, int)));
	else if (specifier == 'u')
		return (ft_print_unsigned(va_arg(args, unsigned int)));
	else if (specifier == 'x')
		return (ft_print_hex_lower(va_arg(args, unsigned int)));
	else if (specifier == 'X')
		return (ft_print_hex_upper(va_arg(args, unsigned int)));
	else if (specifier == '%')
		return (ft_print_percent());
	else
		return (ft_putchar_fd('%', 1));
}

int	ft_parse_format(const char *format, va_list args)
{
	int	count;
	int	i;
	int	ret;

	count = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] != '%')
		{
			ret = ft_putchar_fd(format[i], 1);
			if (ret == -1)
				return (-1);
			count += ret;
			i++;
		}
		else
		{
			i++;
			ret = ft_handle_specifier(format[i], args);
			if (ret == -1)
				return (-1);
			count += ret;
			i++;
		}
	}
	return (count);
}
