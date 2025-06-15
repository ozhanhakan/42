/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntuhakan <ubuntuhakan@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:49:52 by ubuntuhakan       #+#    #+#             */
/*   Updated: 2025/06/15 19:22:39 by ubuntuhakan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	little_len;

	little_len = ft_strlen(little);
	i = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while (big[i] && i + little_len <= len)
	{
		j = 0;
		while ((i + j) < len && little[j] && little[j] == big[i + j])
			j++;
		if (little[j] == '\0')
			return ((char *)&big[i]);
		i++;
	}
	return (0);
}
