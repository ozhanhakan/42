#include <stdio.h>
#include <stdarg.h>

void simple_demo(const char *format, ...)
{
    va_list args;
    printf("=== DEMO START ===\n");
    
    va_start(args, format);
    
    int first = va_arg(args, int);
    printf("First: %d\n", first);
    
    int second = va_arg(args, int);
    printf("Second: %d\n", second);
    
    char *third = va_arg(args, char*);
    printf("Third: %s\n", third);
    
    va_end(args);
    printf("=== DEMO END ===\n");
}

int main(void)
{
    simple_demo("Test", 42, 100, "Hello");
    return 0;
}
