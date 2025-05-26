/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:27:02 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/28 00:05:26 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "do_op.h"

int	execute_operation(int a, char op, int b)
{
	int			i;
	const t_op	ops[] = {
	{'+', op_add},
	{'-', op_sub},
	{'*', op_mul},
	{'/', op_div},
	{'%', op_mod}
	};

	if (b == 0 && (op == '/' || op == '%'))
	{
		if (op == '/')
			ft_putstr("Stop : division by zero\n");
		else
			ft_putstr("Stop : modulo by zero\n");
		return (0);
	}
	i = -1;
	while (++i < 5)
		if (ops[i].op == op)
			ft_putnbr(ops[i].func(a, b));
	ft_putstr("\n");
	return (0);
}

int	main(int argc, char **argv)
{
	int	a;
	int	b;

	if (argc != 4)
		return (0);
	if (!check_operator(argv[2]))
	{
		ft_putstr("0\n");
		return (0);
	}
	a = ft_atoi(argv[1]);
	b = ft_atoi(argv[3]);
	execute_operation(a, argv[2][0], b);
	return (0);
}
/*
 $>./do-op 42 "+" 21
 63
 $>
 $> make clean
 $> make
 $> ./do-op
 $> ./do-op 1 + 1
 2
 $> ./do-op 42amis - --+-20toto12
 62
 $> ./do-op 1 p 1
 0
 $> ./do-op 1 + toto3
 1
 $>
 $> ./do-op toto3 + 4
 4
 $> ./do-op foo plus bar
 0
 $> ./do-op 25 / 0
 Stop : division by zero
 $> ./do-op 25 % 0
 Stop : modulo by zero
 $>

*/