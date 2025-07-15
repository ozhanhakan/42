#include "ft_printf.h"
#include <stdio.h>

int main()
{
    printf("=== DETAILED COMPARISON TEST ===\n\n");
    
    // Test 1: Normal cases
    printf("1. Character test:\n");
    printf("Standard: '%c' -> ", 'A');
    int ret1 = printf("%c", 'A');
    printf(" [ret=%d]\n", ret1);
    
    printf("FT_PRINTF: '%c' -> ", 'A');
    int ret2 = ft_printf("%c", 'A');
    ft_printf(" [ret=%d]\n", ret2);
    printf("Match: %s\n\n", (ret1 == ret2) ? "✅" : "❌");
    
    // Test 2: String
    printf("2. String test:\n");
    printf("Standard: ");
    ret1 = printf("Hello %s!", "World");
    printf(" [ret=%d]\n", ret1);
    
    printf("FT_PRINTF: ");
    ret2 = ft_printf("Hello %s!", "World");
    ft_printf(" [ret=%d]\n", ret2);
    printf("Match: %s\n\n", (ret1 == ret2) ? "✅" : "❌");
    
    // Test 3: Numbers
    printf("3. Number test:\n");
    printf("Standard: ");
    ret1 = printf("Number: %d, Hex: %x, Unsigned: %u", 42, 255, 100);
    printf(" [ret=%d]\n", ret1);
    
    printf("FT_PRINTF: ");
    ret2 = ft_printf("Number: %d, Hex: %x, Unsigned: %u", 42, 255, 100);
    ft_printf(" [ret=%d]\n", ret2);
    printf("Match: %s\n\n", (ret1 == ret2) ? "✅" : "❌");
    
    // Test 4: Percent
    printf("4. Percent test:\n");
    printf("Standard: ");
    ret1 = printf("100%%");
    printf(" [ret=%d]\n", ret1);
    
    printf("FT_PRINTF: ");
    ret2 = ft_printf("100%%");
    ft_printf(" [ret=%d]\n", ret2);
    printf("Match: %s\n\n", (ret1 == ret2) ? "✅" : "❌");
    
    // Test 5: Mixed
    printf("5. Mixed format test:\n");
    printf("Standard: ");
    ret1 = printf("Char: %c, String: %s, Int: %d", 'X', "Test", -123);
    printf(" [ret=%d]\n", ret1);
    
    printf("FT_PRINTF: ");
    ret2 = ft_printf("Char: %c, String: %s, Int: %d", 'X', "Test", -123);
    ft_printf(" [ret=%d]\n", ret2);
    printf("Match: %s\n\n", (ret1 == ret2) ? "✅" : "❌");
    
    printf("=== TEST COMPLETED ===\n");
    return 0;
}
