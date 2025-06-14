#include <stdio.h>

int ft_tolower(int c);

int main(void)
{
    char c;

    c = 'K';
    printf("%c -> %c\n", c, ft_tolower(c)); // K -> k
    c = 'm';
    printf("%c -> %c\n", c, ft_tolower(c)); // m -> m
    c = '9';
    printf("%c -> %c\n", c, ft_tolower(c)); // 9 -> 9
    return (0);
}