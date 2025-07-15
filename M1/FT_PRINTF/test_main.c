#include "ft_printf.h"
#include <stdio.h>

int main(void)
{
    printf("=== FT_PRINTF TEST ===\n");
    
    printf("Testing %%c: ");
    fflush(stdout);  // Flush stdout to ensure output order
    ft_printf("%c\n", 'A');
    
    printf("Testing %%s: ");
    fflush(stdout);  // Flush stdout to ensure output order
    ft_printf("%s\n", "Hello");
    
    printf("Testing %%d: ");
    fflush(stdout);  // Flush stdout to ensure output order 
    ft_printf("%d\n", 42);
    
    printf("Testing %%x: ");
    fflush(stdout);  // Flush stdout to ensure output order
    ft_printf("%x\n", 255);
    
    printf("Testing %%%%: ");
    fflush(stdout);  // Flush stdout to ensure output order
    ft_printf("%%\n");
    
    printf("Test completed!\n");

     int ret1, ret2;
    
    printf("=== STANDARD PRINTF ===\n");
    ret1 = printf("Test: %q %d\n", 42, 100);
    printf("Return value: %d\n", ret1);
    
    printf("\n=== FT_PRINTF ===\n");
    ret2 = ft_printf("Test: %q %d\n", 42, 100);
    ft_printf("Return value: %d\n", ret2);
    
    return (0);
}
