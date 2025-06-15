/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntuhakan <ubuntuhakan@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 19:39:01 by ubuntuhakan       #+#    #+#             */
/*   Updated: 2025/06/15 22:16:10 by ubuntuhakan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	ft_atoi(const char *nptr)
{
	int		c;
	int		s;
	int		res;
	char	*str;

	str = (char *)nptr;
	c = 0;
	s = 1;
	res = 0;
	while (str[c] && (ft_isspace(str[c])))
		c++;
	if (str[c] == '+' || str[c] == '-')
	{
		if (str[c] == '-')
			s *= -1;
		c++;
	}
	while (str[c] && (str[c] >= '0' && str[c] <= '9'))
	{
		res = (str[c] - '0') + (res * 10);
		c++;
	}
	return (res * s);
}
