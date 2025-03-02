/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:00:00 by hozhan            #+#    #+#             */
/*   Updated: 2025/02/19 16:51:56 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/*
 * ft_putchar - Tek bir karakteri standart çıktıya (stdout) yazdırır.
 *
 * @c: Yazdırılacak karakter.
 */
void	ft_putchar(char c)
{
	write(1, &c, 1);
}
