#include "ft_printf.h"
#include <stdio.h>

int main(void)
{
    printf("=== FT_PRINTF TEST ===\n");
    
    printf("Testing %%c: ");
    ft_printf("%c\n", 'A');
    
    printf("Testing %%s: ");
    ft_printf("%s\n", "Hello");
    
    printf("Testing %%d: ");
    ft_printf("%d\n", 42);
    
    printf("Testing %%x: ");
    ft_printf("%x\n", 255);
    
    printf("Testing %%%%: ");
    ft_printf("%%\n");
    
    printf("Test completed!\n");
    return (0);
}
