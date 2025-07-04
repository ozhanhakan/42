#include <stdio.h>
#include <stdlib.h>
#include "../../src/libft.h" // ft_split prototipi burada olmalı

// Yardımcı: ft_split çıktısını yazdır
void	print_split(char **split)
{
	int i = 0;

	if (!split)
	{
		printf("split is NULL\n");
		return;
	}
	while (split[i])
	{
		printf("[%d]: \"%s\"\n", i, split[i]);
		i++;
	}
}

// Yardımcı: ft_split çıktısını temizle
void	free_split(char **split)
{
	int i = 0;

	if (!split)
		return;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	main(void)
{
	char **result;

	// Örnek 1
	result = ft_split("hello world 42", ' ');
	printf("Test 1:\n");
	print_split(result);
	free_split(result);

	// Örnek 2
	result = ft_split(",,,one,,two,,three,,,", ',');
	printf("\nTest 2:\n");
	print_split(result);
	free_split(result);

	// Örnek 3 - Tek kelime
	result = ft_split("onlyone", ' ');
	printf("\nTest 3:\n");
	print_split(result);
	free_split(result);

	// Örnek 4 - Boş string
	result = ft_split("", ' ');
	printf("\nTest 4:\n");
	print_split(result);
	free_split(result);

	// Örnek 5 - NULL girişi
	result = ft_split(NULL, ' ');
	printf("\nTest 5:\n");
	print_split(result);
	free_split(result);

	return (0);
}
