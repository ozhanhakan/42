/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 21:15:29 by hozhan            #+#    #+#             */
/*   Updated: 2025/06/25 17:22:33 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	s_len;
	char	*new_str;	

	if (!s || !f)
		return (NULL);
	s_len = ft_strlen(s);
	new_str = (char *)malloc(sizeof(char) * s_len + 1);
	if (!new_str)
		return (NULL);
	i = -1;
	while (++i < s_len)
		new_str[i] = f((unsigned int)i, s[i]);
	new_str[s_len] = '\0';
	return (new_str);
}
