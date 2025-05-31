#include "../Libft/libft.h"
#include "../Libft/ft_isalpha.c"
#include "../Libft/ft_isdigit.c"
#include "../Libft/ft_isalnum.c"
#include "../Libft/ft_isascii.c"
#include "../Libft/ft_isprint.c"

#include <stdio.h>

#include <ctype.h>


int main(void)
{
	char ch = 'A';

	printf("isalpha('%c') = %d\n", ch, isalpha(ch));    // 1024
	printf("ft_isalpha('%c') = %d\n", ch, ft_isalpha(ch)); // 1

	ch = '0';
	printf("isalpha('%c') = %d\n", ch, isalpha(ch));
	printf("ft_isalpha('%c') = %d\n", ch, ft_isalpha(ch));

	ch = 'A';

	printf("isdigit('%c') = %d\n", ch, isdigit(ch));    // 1024
	printf("ft_isdigit('%c') = %d\n", ch, ft_isdigit(ch)); // 1

	ch = '0';
	printf("isdigit('%c') = %d\n", ch, isdigit(ch));
	printf("ft_isdigit('%c') = %d\n", ch, ft_isdigit(ch));
	
	ch = ' ';

	printf("isalnum('%c') = %d\n", ch, isalnum(ch));    // 1024
	printf("ft_isalnum('%c') = %d\n", ch, ft_isalnum(ch)); // 1

	ch = '0';
	printf("isalnum('%c') = %d\n", ch, isalnum(ch));
	printf("ft_isalnum('%c') = %d\n", ch, ft_isalnum(ch));

	ch = 'a';
	printf("isalnum('%c') = %d\n", ch, isalnum(ch));
	printf("ft_isalnum('%c') = %d\n", ch, ft_isalnum(ch));

	printf("ft_isascii(65): %d\n", ft_isascii(65));   // A → 1
	printf("ft_isascii(127): %d\n", ft_isascii(127)); // DEL → 1
	printf("ft_isascii(128): %d\n", ft_isascii(128)); // → 0
	printf("ft_isascii(0): %d\n", ft_isascii(0));   // → 0

	printf("ft_isprint(32) = %d\n", ft_isprint(32));  // space → 1
	printf("ft_isprint(65) = %d\n", ft_isprint(65));  // 'A' → 1
	printf("ft_isprint(126) = %d\n", ft_isprint(126)); // '~' → 1
	printf("ft_isprint(31) = %d\n", ft_isprint(31));  // → 0
	printf("ft_isprint(127) = %d\n", ft_isprint(127)); // DEL → 0

	return (0);
}