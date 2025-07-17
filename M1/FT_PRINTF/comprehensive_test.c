#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>

void test_char()
{
    printf("=== CHARACTER TESTS (%%c) ===\n");
    
    printf("Standard: ");
    int ret1 = printf("%c", 'A');
    printf(" [ret=%d]\n", ret1);
    
    printf("FT_PRINTF: ");
    int ret2 = ft_printf("%c", 'A');
    ft_printf(" [ret=%d]\n", ret2);
    
    printf("Match: %s\n\n", (ret1 == ret2) ? "✅ YES" : "❌ NO");
}

void test_string()
{
    printf("=== STRING TESTS (%%s) ===\n");
    
    // Normal string
    printf("Standard: ");
    int ret1 = printf("%s", "Hello World");
    printf(" [ret=%d]\n", ret1);
    
    printf("FT_PRINTF: ");
    int ret2 = ft_printf("%s", "Hello World");
    ft_printf(" [ret=%d]\n", ret2);
    
    printf("Match: %s\n", (ret1 == ret2) ? "✅ YES" : "❌ NO");
    
    // NULL string
    printf("\nNULL String Test:\n");
    printf("Standard: ");
    ret1 = printf("%s", (char*)NULL);
    printf(" [ret=%d]\n", ret1);
    
    printf("FT_PRINTF: ");
    ret2 = ft_printf("%s", (char*)NULL);
    ft_printf(" [ret=%d]\n", ret2);
    
    printf("Match: %s\n\n", (ret1 == ret2) ? "✅ YES" : "❌ NO");
}

void test_decimal()
{
    printf("=== DECIMAL TESTS (%%d, %%i) ===\n");
    
    int numbers[] = {42, -42, 0, INT_MAX, INT_MIN};
    int count = 5;
    
    for (int i = 0; i < count; i++)
    {
        printf("Testing %d:\n", numbers[i]);
        
        printf("Standard: ");
        int ret1 = printf("%d", numbers[i]);
        printf(" [ret=%d]\n", ret1);
        
        printf("FT_PRINTF: ");
        int ret2 = ft_printf("%d", numbers[i]);
        ft_printf(" [ret=%d]\n", ret2);
        
        printf("Match: %s\n\n", (ret1 == ret2) ? "✅ YES" : "❌ NO");
    }
}

void test_hex()
{
    printf("=== HEXADECIMAL TESTS (%%x, %%X) ===\n");
    
    unsigned int numbers[] = {42, 255, 0, 0xDEADBEEF};
    int count = 4;
    
    for (int i = 0; i < count; i++)
    {
        printf("Testing 0x%X:\n", numbers[i]);
        
        // Lowercase hex
        printf("Standard (%%x): ");
        int ret1 = printf("%x", numbers[i]);
        printf(" [ret=%d]\n", ret1);
        
        printf("FT_PRINTF (%%x): ");
        int ret2 = ft_printf("%x", numbers[i]);
        ft_printf(" [ret=%d]\n", ret2);
        
        printf("Match: %s\n", (ret1 == ret2) ? "✅ YES" : "❌ NO");
        
        // Uppercase hex
        printf("Standard (%%X): ");
        ret1 = printf("%X", numbers[i]);
        printf(" [ret=%d]\n", ret1);
        
        printf("FT_PRINTF (%%X): ");
        ret2 = ft_printf("%X", numbers[i]);
        ft_printf(" [ret=%d]\n", ret2);
        
        printf("Match: %s\n\n", (ret1 == ret2) ? "✅ YES" : "❌ NO");
    }
}

void test_unknown_specifier()
{
    printf("=== UNKNOWN SPECIFIER TESTS ===\n");
    
    printf("Testing %%q:\n");
    printf("Standard: ");
    int ret1 = printf("%q");
    printf(" [ret=%d]\n", ret1);
    
    printf("FT_PRINTF: ");
    int ret2 = ft_printf("%q");
    ft_printf(" [ret=%d]\n", ret2);
    
    printf("Match: %s\n\n", (ret1 == ret2) ? "✅ YES" : "❌ NO");
}

int main()
{
    printf("🧪 COMPREHENSIVE FT_PRINTF TESTING 🧪\n");
    printf("=====================================\n\n");
    
    test_char();
    test_string();
    test_decimal();
    test_hex();
    test_unknown_specifier();
    
    printf("✅ ALL TESTS COMPLETED!\n");
    
    return 0;
}
