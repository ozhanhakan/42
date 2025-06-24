#include "../src/libft.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void	test_ft_isalpha(void)
{
	printf("ft_isalpha test: ");
	if (ft_isalpha('a') &&
		ft_isalpha('Z') &&
		!ft_isalpha('o'))
		printf("OK\n");
	else
		printf("FAIL\n");
}

void	test_ft_isdigit(void)
{
	printf("ft_isdigit test: ");
	if (ft_isdigit('0') &&
		ft_isdigit('1') &&
		!ft_isdigit(' '))
		printf("OK\n");
	else
		printf("FAIL\n");
}

void	test_ft_isalnum(void)
{
	printf("ft_isalnum test: ");
	if (ft_isalnum('0') &&
		ft_isalnum('k') &&
		!ft_isalnum(' '))
		printf("OK\n");
	else
		printf("FAIL\n");
}

void	test_ft_isascii(void)
{
	printf("ft_isascii test: ");
	if (ft_isascii('\0') &&
		ft_isascii(' ') &&
		!ft_isascii(128))
		printf("OK\n");
	else
		printf("FAIL\n");
}

void	test_ft_isprint(void)
{
	printf("ft_isprint test: ");
	if (!ft_isprint(1) &&
		!ft_isprint(127) &&
		ft_isprint(125))
		printf("OK\n");
	else
		printf("FAIL\n");
}

void	test_ft_strlen(void)
{
	printf("ft_strlen test: ");
	if (ft_strlen("test") == 4 &&
		ft_strlen("") == 0)
		printf("OK\n");
	else
		printf("FAIL\n");
}

void	test_ft_memset(void)
{
	printf("ft_memset test: ");
	char buf[5] = "test";
	ft_memset(buf, 'A', 3);
	if (strcmp(buf, "AAAt") == 0 &&
		buf[2] == 'A')
		printf("OK\n");
	else
		printf("FAIL\n");
	
	int nums [] = {0xFFFF, 0xFFFF, 0xFFFF};
	printf("\nint nums dizisi\n");
	for(int i=0; i<3; i++)
		printf("%X, ", nums[i]);
	ft_memset(nums,0x00,  1); //sizeof(int) *
	printf("\nmemset sonrası int nums dizisi\n");
	for(int i=0; i<3; i++)
		printf("%X, ", nums[i]);
}

void	test_ft_bzero(void)
{
	printf("ft_bzero test: ");
	char	buf[]="test";
	ft_bzero(buf, 3);
	if (buf[0] == 0 && buf[1] == 0 && buf[2]==0 && buf[3]=='t')
		printf("OK\n");
	else
		printf("FAIL\n");
	
	int nums [] = {0xFFFF, 0xFFFF, 0xFFFF};
	printf("\nint nums dizisi\n");
	for(int i=0; i<3; i++)
		printf("%X, ", nums[i]);
	ft_bzero(nums, 1); //sizeof(int) *
	printf("\nbzero sonrası int nums dizisi\n");
	for(int i=0; i<3; i++)
		printf("%X, ", nums[i]);
}

int	main( int argc, char *argv[])
{
	printf("argc: %d, argv[0]: %s, argv[1]: %s\n", argc, argv[0], argv[1]);
	// test_ft_isalpha();
	// test_ft_isdigit();
	// test_ft_isalnum();
	// test_ft_isascii();
	// test_ft_isprint();
	// test_ft_strlen();
	// test_ft_memset();
	// test_ft_bzero();
	
	return (0);
}
