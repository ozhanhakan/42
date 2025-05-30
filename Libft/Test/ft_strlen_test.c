#include <stdio.h>
#include "../Libft/libft.h"

int main(void)
{
	printf("''        -> %ld\n", ft_strlen(""));         //0
	printf("'Hello'   -> %zu\n", ft_strlen("Hello"));    // 5
	printf("'42'      -> %zu\n", ft_strlen("42"));       // 2
	printf("'abcdef'  -> %zu\n", ft_strlen("abcdef"));   // 6
	return (0);
}