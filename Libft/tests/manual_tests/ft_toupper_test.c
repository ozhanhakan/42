#include <stdio.h>

int ft_toupper(int c);

int main(void)
{
    char c;

    c = 'a';
    printf("%c -> %c\n", c, ft_toupper(c)); // a -> A
    c = 'Z';
    printf("%c -> %c\n", c, ft_toupper(c)); // Z -> Z
    c = '5';
    printf("%c -> %c\n", c, ft_toupper(c)); // 5 -> 5
    return (0);
}