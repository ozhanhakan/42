# 📝 FT_PRINTF - 42 School Project

## 🎯 Project Overview

**ft_printf** is a custom implementation of the standard C library function `printf()`. This project is part of the 42 School curriculum and focuses on **variadic functions**, **format specifier parsing**, and **type conversion**.

### 🔍 What is printf?

`printf()` is a formatted output function that:
- Takes a format string with placeholders (format specifiers)
- Accepts variable number of arguments
- Converts and formats the arguments according to specifiers
- Outputs the formatted result to stdout

```c
printf("Hello %s! You have %d messages.\n", "Alice", 5);
// Output: Hello Alice! You have 5 messages.
```

---

## 🚀 Supported Format Specifiers

| Specifier | Type | Description | Example |
|-----------|------|-------------|---------|
| `%c` | `char` | Single character | `ft_printf("%c", 'A')` → `A` |
| `%s` | `char *` | String | `ft_printf("%s", "Hello")` → `Hello` |
| `%p` | `void *` | Pointer address | `ft_printf("%p", ptr)` → `0x7fff5fbff8a0` |
| `%d` | `int` | Signed decimal | `ft_printf("%d", -42)` → `-42` |
| `%i` | `int` | Signed integer | `ft_printf("%i", 42)` → `42` |
| `%u` | `unsigned int` | Unsigned decimal | `ft_printf("%u", 42U)` → `42` |
| `%x` | `unsigned int` | Lowercase hex | `ft_printf("%x", 255)` → `ff` |
| `%X` | `unsigned int` | Uppercase hex | `ft_printf("%X", 255)` → `FF` |
| `%%` | - | Literal percent | `ft_printf("%%")` → `%` |

---

## 🧠 Variadic Functions Explained

### What are Variadic Functions?

Variadic functions can accept a **variable number of arguments**. In C, this is achieved using the `<stdarg.h>` library.

```c
#include <stdarg.h>

// Function that accepts format string + variable arguments
int ft_printf(const char *format, ...);
```

### How Variadic Functions Work

1. **`va_list`** - Type to hold argument information
2. **`va_start(ap, last_param)`** - Initialize argument list
3. **`va_arg(ap, type)`** - Get next argument of specified type
4. **`va_end(ap)`** - Clean up argument list

```c
int ft_printf(const char *format, ...)
{
    va_list args;           // Declare argument list
    va_start(args, format); // Initialize with last fixed parameter
    
    // Process each character in format string
    while (*format)
    {
        if (*format == '%')
        {
            format++; // Skip '%'
            
            // Get argument based on format specifier
            if (*format == 'd')
            {
                int num = va_arg(args, int);  // Extract int argument
                // Convert and print num
            }
            else if (*format == 's')
            {
                char *str = va_arg(args, char *);  // Extract string
                // Print string
            }
        }
        format++;
    }
    
    va_end(args);  // Clean up
    return (char_count);
}
```

### 🔍 Argument Promotion Rules

When arguments are passed to variadic functions, C automatically promotes smaller types:

- `char` → `int`
- `short` → `int`  
- `float` → `double`

```c
// When calling: ft_printf("%c", 'A')
// 'A' is promoted to int, so we extract it as int:
int c = va_arg(args, int);  // Not va_arg(args, char)!
```

---

## 🏗️ Project Structure

```
FT_PRINTF/
├── ft_printf.h              # Header with prototypes and documentation
├── ft_printf.c              # Main printf implementation
├── ft_printf_handlers.c     # Format specifier handler functions
├── ft_printf_utils.c        # Utility functions (putchar, itoa, etc.)
├── Makefile                 # Build system
├── test_main.c              # Comprehensive test suite
└── README.md               # This documentation
```

### 📁 File Descriptions

- **`ft_printf.h`** - Contains function prototypes, includes, and detailed documentation about variadic functions
- **`ft_printf.c`** - Main printf logic with format string parsing and argument extraction
- **`ft_printf_handlers.c`** - Individual functions for each format specifier (%c, %s, %d, etc.)
- **`ft_printf_utils.c`** - Helper functions for string manipulation, number conversion, and output

---

## 🔧 Installation & Usage

### Build the Library

```bash
# Clone or navigate to project directory
cd ft_printf

# Build the static library
make

# This creates: libftprintf.a
```

### Test the Implementation

```bash
# Build and run comprehensive tests
make test
./test_printf

# Check norminette compliance (42 coding standard)
make norm

# Clean temporary files
make clean

# Full clean (removes library too)
make fclean

# Rebuild everything
make re
```

### Use in Your Project

```c
// your_program.c
#include "ft_printf.h"

int main(void)
{
    int count;
    
    // Basic usage
    ft_printf("Hello World!\n");
    
    // With format specifiers
    count = ft_printf("Name: %s, Age: %d, Score: %.2f%%\n", 
                      "Alice", 25, 87.5);
    
    ft_printf("Printed %d characters\n", count);
    
    return (0);
}
```

```bash
# Compile with the library
gcc -Wall -Wextra -Werror your_program.c -L. -lftprintf -o your_program
./your_program
```

---

## 🧪 Testing Strategy

### Test Categories

1. **Format Specifier Tests** - Each %c, %s, %d, etc.
2. **Edge Cases** - NULL pointers, empty strings, INT_MIN/MAX
3. **Return Value Tests** - Character count accuracy
4. **Memory Tests** - No leaks, proper malloc/free
5. **Performance Tests** - Multiple specifiers, long formats

### Sample Test Output

```
=== CHARACTER TESTS (%c) ===

Test 1: Single character
ft_printf:  A (returned: 1)
printf:     A (returned: 1)
✓ PASS

Test 2: NULL string
ft_printf:  (null) (returned: 6)
printf:     (null) (returned: 6)
✓ PASS
```

---

## 🎓 Learning Objectives

By completing this project, you will understand:

### 1. **Variadic Functions**
- How `va_list`, `va_start`, `va_arg`, `va_end` work
- Argument promotion rules in C
- Stack memory layout for function calls

### 2. **Format String Parsing**
- State machine concepts
- Character-by-character processing
- Format specifier recognition

### 3. **Type Conversion**
- Integer to string conversion (decimal, hexadecimal)
- Memory address formatting
- Unsigned vs signed number handling

### 4. **Memory Management**
- Dynamic allocation for number conversion
- Preventing memory leaks
- Buffer management

### 5. **System Programming**
- `write()` system call usage
- File descriptor concepts
- Low-level output operations

---

## 🔍 Key Implementation Details

### Format Parsing Algorithm

```c
// Simplified parsing logic
while (*format)
{
    if (*format == '%')
    {
        format++;  // Skip '%'
        
        // Parse format specifier
        switch (*format)
        {
            case 'c': count += ft_print_char(va_arg(args, int)); break;
            case 's': count += ft_print_string(va_arg(args, char *)); break;
            case 'd': count += ft_print_decimal(va_arg(args, int)); break;
            // ... other specifiers
        }
    }
    else
    {
        // Regular character - just print it
        count += ft_putchar_fd(*format, 1);
    }
    format++;
}
```

### Number to String Conversion

```c
// Example: Convert 42 to "42"
char *ft_itoa(int n)
{
    // 1. Handle sign (negative numbers)
    // 2. Count digits needed
    // 3. Allocate string memory
    // 4. Convert from right to left:
    //    - 42 % 10 = 2 → str[1] = '2'
    //    - 42 / 10 = 4 → 4 % 10 = 4 → str[0] = '4'
    // 5. Return "42"
}
```

### Pointer Address Formatting

```c
// Example: Convert pointer 0x7fff5fbff8a0 to "0x7fff5fbff8a0"
int ft_print_pointer(void *ptr)
{
    if (!ptr)
        return ft_putstr_fd("(nil)", 1);
    
    count += ft_putstr_fd("0x", 1);  // Prefix
    count += ft_itoa_base((unsigned long)ptr, "0123456789abcdef");
    return count;
}
```

---

## 📚 Resources & References

### C Standards & Documentation
- [C11 Standard - Variadic Functions](https://en.cppreference.com/w/c/variadic)
- [printf() Specification](https://man7.org/linux/man-pages/man3/printf.3.html)
- [stdarg.h Documentation](https://en.cppreference.com/w/c/variadic)

### 42 School Resources
- [42 Norminette](https://github.com/42School/norminette) - Coding standard checker
- [42 Header](https://github.com/42Paris/42header) - Standard file header

### Additional Learning
- [Understanding Variadic Functions](https://www.cprogramming.com/tutorial/c/lesson17.html)
- [printf Implementation Tutorial](https://iq.opengenus.org/how-printf-works-internally/)

---

## 🤝 Contributing

This is an educational project for 42 School. However, suggestions for improvements are welcome:

1. **Code Review** - Check for edge cases or optimizations
2. **Test Cases** - Add more comprehensive tests
3. **Documentation** - Improve explanations or add examples
4. **Performance** - Suggest algorithmic improvements

---

## ⚠️ Important Notes

### Limitations
- No flag handling (`-`, `+`, `#`, ` `, `0`)
- No width/precision specifiers
- No length modifiers (`l`, `ll`, `h`, etc.)
- Only required format specifiers implemented

### Performance Considerations
- Each number conversion allocates memory - consider buffer pooling for production use
- Multiple `write()` calls - could be optimized with internal buffering
- Recursive string building - iterative approach might be more efficient

---

## 📄 License

This project is part of 42 School curriculum. Code is provided for educational purposes.

---

