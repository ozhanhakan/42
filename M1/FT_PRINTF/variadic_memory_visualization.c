#include <stdio.h>
#include <stdarg.h>

void visualize_stack_before_call(void)
{
    printf("=== STACK BEFORE FUNCTION CALL ===\n");
    printf("Before: func(\"%%d %%c %%s\", 42, 'A', \"Hello\")\n\n");
    
    printf("Stack preparation:\n");
    printf("1. Push \"Hello\" pointer to stack\n");
    printf("2. Push 'A' (promoted to int) to stack\n");
    printf("3. Push 42 to stack\n");
    printf("4. Push format string pointer to stack\n");
    printf("5. Call function\n\n");
}

void visualize_stack_layout(void)
{
    printf("=== DETAILED STACK LAYOUT ===\n");
    printf("Memory addresses (example on 64-bit):\n\n");
    
    printf("Higher Address\n");
    printf("┌─────────────────────────────────────┐ 0x7fff0028\n");
    printf("│        \"Hello\" pointer              │ <- 8 bytes\n");
    printf("│      (0x0000000012345678)           │\n");
    printf("├─────────────────────────────────────┤ 0x7fff0020\n");
    printf("│    'A' (65) + 4 bytes padding      │ <- 8 bytes total\n");
    printf("│      (0x0000004100000000)           │\n");
    printf("├─────────────────────────────────────┤ 0x7fff0018\n");
    printf("│     42 + 4 bytes padding           │ <- 8 bytes total\n");
    printf("│      (0x0000002A00000000)           │\n");
    printf("├─────────────────────────────────────┤ 0x7fff0010\n");
    printf("│      format string pointer         │ <- 8 bytes\n");
    printf("│      (0x0000000087654321)           │\n");
    printf("├─────────────────────────────────────┤ 0x7fff0008\n");
    printf("│         return address              │\n");
    printf("└─────────────────────────────────────┘\n");
    printf("Lower Address\n\n");
}

void visualize_va_operations(void)
{
    printf("=== VA_OPERATIONS VISUALIZATION ===\n");
    
    printf("Step 1: va_start(args, format)\n");
    printf("┌─────────────────────────────────────┐\n");
    printf("│        \"Hello\" pointer              │\n");
    printf("├─────────────────────────────────────┤\n");
    printf("│           'A' (65)                  │\n");
    printf("├─────────────────────────────────────┤\n");
    printf("│             42                      │ <- args points here\n");
    printf("├─────────────────────────────────────┤\n");
    printf("│      format string pointer         │\n");
    printf("└─────────────────────────────────────┘\n\n");
    
    printf("Step 2: va_arg(args, int) - Read 42\n");
    printf("┌─────────────────────────────────────┐\n");
    printf("│        \"Hello\" pointer              │\n");
    printf("├─────────────────────────────────────┤\n");
    printf("│           'A' (65)                  │ <- args points here\n");
    printf("├─────────────────────────────────────┤\n");
    printf("│             42                      │ <- just read\n");
    printf("├─────────────────────────────────────┤\n");
    printf("│      format string pointer         │\n");
    printf("└─────────────────────────────────────┘\n\n");
    
    printf("Step 3: va_arg(args, int) - Read 'A'\n");
    printf("┌─────────────────────────────────────┐\n");
    printf("│        \"Hello\" pointer              │ <- args points here\n");
    printf("├─────────────────────────────────────┤\n");
    printf("│           'A' (65)                  │ <- just read\n");
    printf("├─────────────────────────────────────┤\n");
    printf("│             42                      │\n");
    printf("├─────────────────────────────────────┤\n");
    printf("│      format string pointer         │\n");
    printf("└─────────────────────────────────────┘\n\n");
    
    printf("Step 4: va_arg(args, char*) - Read \"Hello\"\n");
    printf("┌─────────────────────────────────────┐\n");
    printf("│        \"Hello\" pointer              │ <- just read\n");
    printf("├─────────────────────────────────────┤\n");
    printf("│           'A' (65)                  │\n");
    printf("├─────────────────────────────────────┤\n");
    printf("│             42                      │\n");
    printf("├─────────────────────────────────────┤\n");
    printf("│      format string pointer         │\n");
    printf("└─────────────────────────────────────┘\n\n");
}

void demonstrate_real_access(const char *format, ...)
{
    va_list args;
    
    printf("=== REAL ACCESS DEMONSTRATION ===\n");
    
    va_start(args, format);
    
    printf("Reading arguments in order:\n");
    
    int first = va_arg(args, int);
    printf("1. Got integer: %d\n", first);
    
    int second = va_arg(args, int);
    printf("2. Got integer (char): %d ('%c')\n", second, (char)second);
    
    char *third = va_arg(args, char*);
    printf("3. Got string: %s\n", third);
    
    va_end(args);
    
    printf("=== ACCESS COMPLETE ===\n\n");
}

int main(void)
{
    printf("VARIADIC MEMORY COMPLETE VISUALIZATION\n");
    printf("=====================================\n\n");
    
    visualize_stack_before_call();
    visualize_stack_layout();
    visualize_va_operations();
    
    demonstrate_real_access("Format: %d %c %s", 42, 'A', "Hello");
    
    return 0;
}