#include "libft.h"
#include <stdio.h>

int main (void)
{
	/* // is functions
	char alpha = 'a';
	char alnum = '1';
	char ascii= ' ';
	char digit= '0';
	char print='/';

	printf("%c: %s \n", alpha, ft_isalpha(alpha) ? "EVET" : "HAYIR");
	printf("%c: %s \n", alnum, ft_isalnum(alnum) ? "EVET" : "HAYIR");
	printf("%c: %s \n", ascii, ft_isascii(ascii) ? "EVET" : "HAYIR");
	printf("%c: %s \n", digit, ft_isdigit(digit) ? "EVET" : "HAYIR");
	printf("%c: %s \n", print, ft_isprint(print) ? "EVET" : "HAYIR");
	 */
	
	/*  //strlen
	printf("%zu\n", ft_strlen("ogrenci"));
	 */
	
	 //memcpy, memmove
	 char s[]="1234567890";
	 char s1[11];
	 
	 printf("s: %s , s1: %s\n",s, (char *)ft_memcpy(s1, s, ft_strlen(s) + 1));
	 for(int i = 0; i<10; i++)
	 	printf("%c, ",s1[i]);
	printf("\n");
printf("memcpy\n");
	 printf("s1: %s , s1: %s\n",s1, (char *)ft_memcpy(s1, "1234567890", 11));
	 printf("s1: %s , s1+2: %s\n",s1, (char *)ft_memcpy(s1 + 2, s1 , 5));
	printf("memmove\n");
	 printf("s1: %s , s1: %s\n",s1, (char *)ft_memmove(s1, "1234567890", 11));
	 printf("s1: %s , s1+2: %s\n",s1, (char *)ft_memmove(s1 + 2, s1 , 5));

	return (0);
}