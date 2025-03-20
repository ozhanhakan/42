/* #include "../C08/ex00/ft.h" //ex00 test
#include <stdio.h>

int main(void)
{
    ft_putchar('C');
    return (0);
}

#include <unistd.h>
void	ft_putchar(char c)
{
	write(1,&c,1);
} */

/* 
//ex01
#include "../C08/ex01/ft_boolean.h"

void    ft_putstr(char *str)
{
    while (*str)
        write(1, str++, 1);
}

t_bool  ft_is_even(int nbr)
{
    return (EVEN(nbr) ? TRUE : FALSE);
}

int main(int argc, char **argv)
{
    (void)argv;
    if (ft_is_even(argc - 1) == TRUE)
        ft_putstr(EVEN_MSG);
    else
        ft_putstr(ODD_MSG);
    return (SUCCESS);
} */
/* 
#include <stdio.h>
#include "../C08/ex02/ft_abs.h"

int main(void)
{
    printf("ABS(-5) = %d\n", ABS(-5));
    printf("ABS(-10) = %d\n", ABS(10));
    printf("ABS(0) = %d\n", ABS(0));
    printf("ABS(5) = %d\n", ABS(5));
    printf("ABS(10) = %d\n", ABS(10));
    return (0);
} */

#include "../C08/ex03/ft_point.h"

// set_point fonksiyonunu tanımla
void set_point(t_point *point) {
    point->x = 42;
    point->y = 21;
}
#include <stdio.h>
int main(void) {
    t_point point;
    set_point(&point);  // point yapısının adresini fonksiyona gönder
    printf("x: %d, y: %d\n", point.x, point.y);
    return 0;
}
