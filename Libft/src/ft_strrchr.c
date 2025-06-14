/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntuhakan <ubuntuhakan@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 23:48:56 by ubuntuhakan       #+#    #+#             */
/*   Updated: 2025/06/15 00:15:50 by ubuntuhakan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	size_t	i;

	ptr = (char *)s;
	i = ft_strlen(s);
	if ((char)c == '\0')
		return (ptr + i);
	while (i)
	{
		if (ptr[i - 1] == (char)c)
			return (ptr + i - 1);
		i--;
	}
	return (NULL);
}
