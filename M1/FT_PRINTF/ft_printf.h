/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:20:23 by hozhan            #+#    #+#             */
/*   Updated: 2025/07/15 17:20:43 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>

int		ft_printf(const char *format, ...);
int		ft_parse_format(const char *format, va_list args);

int		ft_print_char(int c);
int		ft_print_string(char *str);
int		ft_print_pointer(void *ptr);
int		ft_print_decimal(int n);
int		ft_print_unsigned(unsigned int n);
int		ft_print_hex_lower(unsigned int n);
int		ft_print_hex_upper(unsigned int n);
int		ft_print_percent(void);

int		ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
char	*ft_itoa(int n);
char	*ft_utoa(unsigned int n);
char	*ft_itoa_base(unsigned long n, char *base);

#endif
