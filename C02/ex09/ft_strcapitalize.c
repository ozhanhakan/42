/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 21:23:37 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/02 22:48:54 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_alpha(char c);
int	ft_is_numeric(char c);
char	*ft_strlowcase(char *str);

char	*ft_strcapitalize(char *str)
{
	int	i;
	int	first;
	int	alpha;

	i = 0;
	str = ft_strlowcase(str);
	first = 1;
	while (str[i])
	{
		alpha = ft_is_alpha(str[i]);
		if(first && alpha)
		{
			str[i] = 'A' + str[i] - 'a';
			first = 0;
		}
		if(!alpha)
			first = 1;
		if(ft_is_numeric(str[i]))
			first = 0;
		i++;
	}
	return str;
}

char *ft_strlowcase(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] = 'a' + str[i] - 'A';
		i++;
	}
	return str;
}

int	ft_is_numeric(char c)
{
		if ((c >= '0') && (c <= '9'))
			return (1);
		return (0);
}

int	ft_is_alpha(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

/* 
#include <stdio.h>

int	main(void)
{
char	temp[] ="salut, comment tu vas ? 42mpts quarante-deux; cinquante+et+un";
printf("%s\n", ft_strcapitalize(temp));
}
 */