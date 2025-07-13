#include <stdio.h>
#include <stdarg.h>

void show_va_list_structure(void)
{
    printf("=== VA_LIST STRUCTURE ===\n");
    printf("va_list is essentially a pointer to stack arguments\n");
    printf("It contains:\n");
    printf("- Current position in argument stack\n");
    printf("- Information about processed arguments\n\n");
}

void show_va_start_operation(void)
{
    printf("=== VA_START OPERATION ===\n");
    printf("va_start(args, format) does:\n");
    printf("1. Calculate address of first variadic argument\n");
    printf("2. Initialize args to point to that address\n");
    printf("3. Set up internal bookkeeping\n\n");
    
    printf("Formula: args = (char*)&format + sizeof(format)\n");
    printf("But actually uses compiler-specific implementation\n\n");
}

void show_va_arg_operation(void)
{
    printf("=== VA_ARG OPERATION ===\n");
    printf("va_arg(args, type) does:\n");
    printf("1. Read sizeof(type) bytes from current position\n");
    printf("2. Cast the data to specified type\n");
    printf("3. Move pointer forward by aligned size\n");
    printf("4. Return the value\n\n");
    
    printf("Important: Type must match exactly what was passed!\n\n");
}

void show_va_end_operation(void)
{
    printf("=== VA_END OPERATION ===\n");
    printf("va_end(args) does:\n");
    printf("1. Clean up internal state\n");
    printf("2. Set args to invalid state\n");
    printf("3. Prevent further access\n\n");
    
    printf("This is mandatory for proper cleanup!\n\n");
}

void demonstrate_step_by_step(const char *format, ...)
{
    va_list args;
    
    printf("=== STEP BY STEP DEMO ===\n");
    printf("Called with format: %s\n", format);
    
    printf("\n1. Before va_start:\n");
    printf("   args is uninitialized\n");
    
    va_start(args, format);
    printf("\n2. After va_start:\n");
    printf("   args points to first variadic argument\n");
    
    int first = va_arg(args, int);
    printf("\n3. After first va_arg(args, int):\n");
    printf("   Retrieved: %d\n", first);
    printf("   args moved to next argument\n");
    
    int second = va_arg(args, int);
    printf("\n4. After second va_arg(args, int):\n");
    printf("   Retrieved: %d ('%c')\n", second, (char)second);
    printf("   args moved to next argument\n");
    
    char *third = va_arg(args, char*);
    printf("\n5. After third va_arg(args, char*):\n");
    printf("   Retrieved: %s\n", third);
    printf("   args moved to next argument\n");
    
    printf("\n6. Before va_end:\n");
    printf("   args still valid but should be cleaned up\n");
    
    va_end(args);
    printf("\n7. After va_end:\n");
    printf("   args is now invalid and cleaned up\n");
    
    printf("\n=== STEP BY STEP COMPLETE ===\n\n");
}

int main(void)
{
    printf("VARIADIC MEMORY DETAILED DEMO\n");
    printf("============================\n\n");
    
    show_va_list_structure();
    show_va_start_operation();
    show_va_arg_operation();
    show_va_end_operation();
    
    demonstrate_step_by_step("Demo: %d %c %s", 42, 'A', "Hello");
    
    return 0;
}