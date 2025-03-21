/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 00:26:35 by hozhan            #+#    #+#             */
/*   Updated: 2025/03/21 11:51:31 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Açıklamalar
* is_sep fonksiyonu, verilen karakterin charset içerisinde olup olmadığını,
* count_words fonksiyonu, boş olmayan kelimelerin sayısını belirler.
* word_dup fonksiyonu, belirlenen kelime aralığından dinamik olarak string ypr
* ft_split fonksiyonu, verilen diziyi ayırarak her kelime için bellek ayırır 
	ve son elemanı NULL olacak şekilde bir dizi döner.
*/

#include <stdlib.h>

int	is_sep(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int	count_words(char *str, char *charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (!is_sep(str[i], charset))
		{
			if (str[i + 1] == '\0' || is_sep(str[i + 1], charset))
				count++;
		}
		i++;
	}
	return (count);
}

char	*word_dup(char *str, int start, int end)
{
	char	*word;
	int		i;

	word = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (0);
	i = 0;
	while (start < end)
	{
		word[i] = str[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char *str, char *charset)
{
	char	**split;
	int		i;
	int		j;
	int		index;

	split = (char **)malloc(sizeof(char *) * (count_words(str, charset) + 1));
	if (!split)
		return (0);
	i = 0;
	index = 0;
	while (str[i])
	{
		if (!is_sep(str[i], charset))
		{
			j = i;
			while (str[j] && !is_sep(str[j], charset))
				j++;
			split[index++] = word_dup(str, i, j);
			i = j;
		}
		else
			i++;
	}
	split[index] = 0;
	return (split);
}
/* 
//Test fonksiyonu
#include <stdio.h>

int	main(void)
{
	char	*str = "Hello,world!This-is:a.test";
	char	*charset = ",!-:.";
	char	**result = ft_split(str, charset);

	if(result)
	{
		for(int i=0; result[i];i++)
		{
			printf("%s\n", result[i]);
			free(result[i]);//her ek string belleğini serbest bırak
		}
		free(result);
	}
	else
		printf("Bellek Hatası");
	return (0);
} */