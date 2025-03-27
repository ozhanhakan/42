/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 22:43:47 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/27 23:27:39 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "do_op.h"

int	op_add(int a, int b)
{
	return (a + b);
}

int	op_sub(int a, int b)
{
	return (a - b);
}

int	op_mul(int a, int b)
{
	return (a * b);
}

int	op_div(int a, int b)
{
	if (b == 0)
	{
		ft_putstr("Stop : division by zero\n");
		return (0);
	}
	return (a / b);
}

int	op_mod(int a, int b)
{
	if (b == 0)
	{
		ft_putstr("Stop : modulo by zero\n");
		return (0);
	}
	return (a % b);
}
