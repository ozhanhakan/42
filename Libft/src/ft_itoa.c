/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:20:38 by hozhan            #+#    #+#             */
/*   Updated: 2025/06/18 18:36:19 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include <limits.h>

static int	ft_int_len(int n)
{
	int			len;
	long long	nb;

	len = 0;
	nb = n;
	if (n == 0)
		return (1);
	if (nb < 0)
	{
		len++;
		nb = -nb;
	}
	while (nb > 0)
	{
		len++;
		nb /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			len;
	long long	nb;

	len = ft_int_len(n);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	nb = n;
	if (nb == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (nb < 0)
		nb = -nb;
	while (nb > 0)
	{
		str[--len] = (nb % 10) + '0';
		nb /= 10;
	}
	if (n < 0)
		str[--len] = '-';
	return (str);
}
