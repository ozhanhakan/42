#include <stdio.h>
#include <stdarg.h>

void show_type_promotion(void)
{
    printf("=== TYPE PROMOTION DEMO ===\n");
    printf("In variadic functions:\n");
    printf("- char -> int (promoted)\n");
    printf("- short -> int (promoted)\n");
    printf("- float -> double (promoted)\n");
    printf("- int -> int (no change)\n");
    printf("- char* -> char* (no change)\n\n");
    
    printf("Example: 'A' character\n");
    printf("- Sent as: 'A' (char)\n");
    printf("- Stored as: %d (int)\n", 'A');
    printf("- Retrieved with: va_arg(args, int)\n\n");
}

void show_memory_alignment(void)
{
    printf("=== MEMORY ALIGNMENT ===\n");
    printf("On 64-bit systems:\n");
    printf("- int: 4 bytes + 4 bytes padding = 8 bytes\n");
    printf("- char*: 8 bytes (no padding needed)\n");
    printf("- double: 8 bytes (no padding needed)\n");
    printf("- void*: 8 bytes (no padding needed)\n\n");
    
    printf("Stack layout example:\n");
    printf("Address:    Content:\n");
    printf("0x7fff0020: [\"Hello\" pointer]  (8 bytes)\n");
    printf("0x7fff0018: ['A' + padding]    (8 bytes)\n");
    printf("0x7fff0010: [42 + padding]     (8 bytes)\n");
    printf("0x7fff0008: [format pointer]   (8 bytes)\n\n");
}

void demonstrate_memory_access(const char *format, ...)
{
    va_list args;
    
    printf("=== MEMORY ACCESS DEMO ===\n");
    printf("Function called with: %s\n", format);
    
    va_start(args, format);
    
    printf("Step 1: va_start(args, format)\n");
    printf("  - args now points to first variadic argument\n");
    
    int first = va_arg(args, int);
    printf("Step 2: va_arg(args, int)\n");
    printf("  - Read 4 bytes from stack: %d\n", first);
    printf("  - Move args pointer forward by 8 bytes (with padding)\n");
    
    int second = va_arg(args, int);
    printf("Step 3: va_arg(args, int) [for char]\n");
    printf("  - Read 4 bytes from stack: %d ('%c')\n", second, (char)second);
    printf("  - Move args pointer forward by 8 bytes (with padding)\n");
    
    char *third = va_arg(args, char*);
    printf("Step 4: va_arg(args, char*)\n");
    printf("  - Read 8 bytes from stack: %s\n", third);
    printf("  - Move args pointer forward by 8 bytes\n");
    
    printf("Step 5: va_end(args)\n");
    printf("  - Clean up args pointer\n");
    
    va_end(args);
    printf("=== MEMORY ACCESS COMPLETE ===\n\n");
}

int main(void)
{
    printf("VARIADIC MEMORY DEMONSTRATION\n");
    printf("============================\n\n");
    
    show_type_promotion();
    show_memory_alignment();
    demonstrate_memory_access("Test: %d %c %s", 42, 'A', "Hello");
    
    return 0;
}