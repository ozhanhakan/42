/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 07:51:54 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/11 11:39:29 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iterative_factorial(int nb)
{
	int	num;

	if (nb < 0)
		return (0);
	else if (nb == 0)
		return (1);
	num = nb;
	nb--;
	while (nb > 1)
	{
		num = num * nb;
		nb--;
	}
	return (num);
}
