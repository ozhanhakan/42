#include <stdio.h>  // For printf
#include <string.h> // For memset, memcmp
#include <stdlib.h> // For EXIT_SUCCESS, EXIT_FAILURE

// Your ft_memset function prototype (usually in libft.h)
#include "../../src/libft.h" 

// Color definitions (optional, for pretty output)
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define RESET   "\033[0m"

// Helper function to run a single memset test case
void run_memset_test_case(const char *test_name, char *buffer, int val, size_t n, size_t buffer_size) {
    char original_buffer[buffer_size];
    char ft_buffer[buffer_size];
    
    // Initialize buffers for testing
    // If an initial string is provided, copy it. Otherwise, zero-fill.
    if (buffer) {
        memcpy(original_buffer, buffer, buffer_size);
        memcpy(ft_buffer, buffer, buffer_size);
    } else {
        memset(original_buffer, 0, buffer_size);
        memset(ft_buffer, 0, buffer_size);
    }

    // Apply original memset
    memset(original_buffer, val, n);
    // Apply your ft_memset
    ft_memset(ft_buffer, val, n);

    // Compare results
    int success = (memcmp(original_buffer, ft_buffer, buffer_size) == 0);

    printf("Test: %s\n", test_name);
    printf("  Original memset result (hex): ");
    for (size_t i = 0; i < buffer_size; i++) {
        printf("%02x ", (unsigned char)original_buffer[i]);
    }
    printf("\n");

    printf("  ft_memset result (hex):       ");
    for (size_t i = 0; i < buffer_size; i++) {
        printf("%02x ", (unsigned char)ft_buffer[i]);
    }
    printf("\n");

    if (success) {
        printf("%s  [OK] PASSED%s\n\n", GREEN, RESET);
    } else {
        printf("%s  [FAIL] FAILED%s\n", RED, RESET);
        printf("  Mismatch detected!\n\n");
        exit(EXIT_FAILURE); // Exit on failure
    }
}

int main(void) {
    printf("%s=== Manual ft_memset Tests ===%s\n\n", YELLOW, RESET);

    // Test 1: Basic fill
    char buf1_base[10] = {0}; // Start with all zeros
    run_memset_test_case("Basic Fill ('A', 5 bytes)", buf1_base, 'A', 5, 10);

    // Test 2: Fill the entire array
    char buf2_base[5] = {0};
    run_memset_test_case("Full Array Fill ('Z', 5 bytes)", buf2_base, 'Z', 5, 5);

    // Test 3: Fill with zero (null bytes)
    char buf3_base[12] = "Hello World"; // Ensure it's null-terminated if a string literal
    run_memset_test_case("Zero Fill ('\\0', 6 bytes)", buf3_base, 0, 6, 12);

    // Test 4: Size 0 (should change nothing)
    char buf4_base[8] = "Test123";
    run_memset_test_case("Size Zero (0 bytes)", buf4_base, 'X', 0, 8);

    // Test 5: Return value check
    char buffer_ret[10];
    // Call original memset for its side effect (filling the buffer)
    memset(buffer_ret, 'C', 5); 
    // Get ft_memset's return value
    void *ret_ft = ft_memset(buffer_ret, 'C', 5);
    
    printf("Test: Return Value Check\n");
    if (ret_ft == buffer_ret) {
        printf("%s  [OK] Return value matches buffer address%s\n\n", GREEN, RESET);
    } else {
        printf("%s  [FAIL] Return value mismatch%s\n\n", RED, RESET);
        exit(EXIT_FAILURE);
    }

    printf("%s=== All ft_memset manual tests completed successfully! ===%s\n", GREEN, RESET);
    return (EXIT_SUCCESS);
}