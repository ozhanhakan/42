/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_num_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:07:45 by hozhan            #+#    #+#             */
/*   Updated: 2025/07/15 17:25:40 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

static int	ft_count_digits_base(unsigned long n, int base)
{
	int	count;

	if (n == 0)
		return (1);
	
	count = 0;
	while (n > 0)
	{
		n /= base;
		count++;
	}
	
	return (count);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				len;
	int				sign;
	long long		num;

	num = n;
	sign = (num < 0) ? 1 : 0;
	if (sign)
		num = -num;
	len = ft_count_digits_base(num, 10) + sign;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len > sign)
	{
		str[--len] = (num % 10) + '0';
		num /= 10;
	}
	if (sign)
		str[0] = '-';
	return (str);
}

char	*ft_utoa(unsigned int n)
{
	char	*str;
	int		len;

 	len = ft_count_digits_base(n, 10);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len > 0)
	{
		str[--len] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}

char	*ft_itoa_base(unsigned long num, char *base)
{
	char	*str;
	int		len;
	int		base_len;

	if (!base)
		return (NULL);
	
	base_len = (int)ft_strlen(base);
	if (base_len < 2)
		return (NULL);
	len = ft_count_digits_base(num, base_len);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len > 0)
	{
		str[--len] = base[num % base_len];
		num /= base_len;
	}
	return (str);
}
