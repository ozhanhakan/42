#include <stdio.h>
#include <stdarg.h>

void show_memory_layout(void)
{
    printf("=== STACK MEMORY LAYOUT ===\n");
    printf("Example: func(\"%%d %%c %%s\", 42, 'A', \"Hello\")\n\n");
    
    printf("STACK STRUCTURE:\n");
    printf("High Address\n");
    printf("┌─────────────────────────────────────┐\n");
    printf("│     \"Hello\" address (8 bytes)       │\n");
    printf("├─────────────────────────────────────┤\n");
    printf("│     'A' + padding (8 bytes)         │\n");
    printf("├─────────────────────────────────────┤\n");
    printf("│     42 + padding (8 bytes)          │\n");
    printf("├─────────────────────────────────────┤\n");
    printf("│     format string address           │\n");
    printf("└─────────────────────────────────────┘\n");
    printf("Low Address\n\n");
}

void demonstrate_va_arg(const char *format, ...)
{
    va_list args;
    
    printf("=== VA_ARG DEMONSTRATION ===\n");
    printf("Format: %s\n", format);
    
    va_start(args, format);
    
    int first = va_arg(args, int);
    printf("1. va_arg(args, int) = %d\n", first);
    
    int second = va_arg(args, int);
    printf("2. va_arg(args, int) = %d ('%c')\n", second, (char)second);
    
    char *third = va_arg(args, char*);
    printf("3. va_arg(args, char*) = %s\n", third);
    
    va_end(args);
    printf("=== DEMONSTRATION COMPLETE ===\n\n");
}

int main(void)
{
    printf("VARIADIC MEMORY VISUALIZATION\n");
    printf("============================\n\n");
    
    show_memory_layout();
    demonstrate_va_arg("Test: %d %c %s", 42, 'A', "Hello");
    
    return 0;
}