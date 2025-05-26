/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stock_str.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:48:11 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/20 15:48:59 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//moulinette has this file
#ifndef FT_STOCK_STR_H
# define FT_STOCK_STR_H

typedef struct s_stock_str
{
	int size;
	char *str;
	char *copy;
}	t_stock_str;

#endif