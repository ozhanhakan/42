/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_op.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:05:14 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/27 23:24:40 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DO_OP_H
# define DO_OP_H

# include <unistd.h>

typedef struct s_op
{
	char	op;
	int		(*func)(int, int);
}	t_op;

// helpers.c
int		ft_atoi(const char *str);
int		ft_strlen(char *str);
void	ft_putnbr(int n);
void	ft_putstr(char *str);

// validation.c
int		check_operator(char *op);

// operations.c
int		op_add(int a, int b);
int		op_sub(int a, int b);
int		op_mul(int a, int b);
int		op_div(int a, int b);
int		op_mod(int a, int b);

// do_op.c
int		execute_operation(int a, char op, int b);

#endif
