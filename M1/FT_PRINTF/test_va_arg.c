#include <stdio.h>
#include <stdarg.h>

/*
** VA_ARG TEST DOSYASI
** 
** Bu dosya va_arg kavramini detayliyla test eder
*/

void test_va_arg_memory(const char *format, ...)
{
    va_list args;
    
    printf("=== VA_ARG MEMORY TEST ===\n");
    printf("Format: %s\n", format);
    
    va_start(args, format);
    
    // Test 1: Integer
    printf("Test 1 - Integer:\n");
    int num = va_arg(args, int);
    printf("  Alinan deger: %d\n", num);
    
    // Test 2: Character (int olarak)
    printf("Test 2 - Character:\n");
    int ch = va_arg(args, int);
    printf("  Alinan deger: %d ('%c')\n", ch, (char)ch);
    
    // Test 3: String
    printf("Test 3 - String:\n");
    char *str = va_arg(args, char*);
    printf("  Alinan string: %s\n", str);
    
    va_end(args);
    printf("=== TEST TAMAMLANDI ===\n\n");
}

void test_type_promotion(void)
{
    printf("=== TYPE PROMOTION TEST ===\n");
    printf("char -> int promotion:\n");
    printf("'A' karakteri: ASCII %d\n", 'A');
    printf("Stack'te int olarak saklanir\n");
    printf("va_arg(args, int) ile alinir\n\n");
}

int main(void)
{
    printf("VA_ARG KAVRAMI TEST PROGRAMI\n");
    printf("===========================\n\n");
    
    test_type_promotion();
    test_va_arg_memory("Test format", 42, 'A', "Hello World");
    printf("Bu test, va_arg'in bellek ve tip promosyonu davranisini gosterir.\n\n");        
    printf("Açıklama: Her format için farklı tip kullanılır:\n");
    printf("%%d -> va_arg(args, int)\n");
    printf("%%s -> va_arg(args, char *)\n");
    printf("%%p -> va_arg(args, void *)\n");
    printf("%%x -> va_arg(args, unsigned int)\n\n");

    return (0);
}
