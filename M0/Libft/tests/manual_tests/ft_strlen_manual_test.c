#include <stdio.h>  // For printf
#include <string.h> // For strlen
#include <stdlib.h> // For EXIT_SUCCESS, EXIT_FAILURE

// Your ft_strlen function prototype (usually in libft.h)
#include "../../src/libft.h" 

// Color definitions
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define RESET   "\033[0m"

// Helper function to run a single strlen test case
void run_strlen_test_case(const char *test_name, const char *s) {
    size_t original_len = strlen(s);
    size_t ft_len = ft_strlen(s);

    int success = (original_len == ft_len);

    printf("Test: %s\n", test_name);
    printf("  String: \"%s\"\n", s);
    printf("  Original strlen: %zu\n", original_len);
    printf("  ft_strlen:       %zu\n", ft_len);

    if (success) {
        printf("%s  [OK] PASSED%s\n\n", GREEN, RESET);
    } else {
        printf("%s  [FAIL] FAILED%s\n", RED, RESET);
        printf("  Mismatch detected! Expected: %zu, Got: %zu\n\n", original_len, ft_len);
        exit(EXIT_FAILURE); // Exit on failure
    }
}

int main(void) {
    printf("%s=== Manual ft_strlen Tests ===%s\n\n", YELLOW, RESET);

    // Test 1: Basic string
    run_strlen_test_case("Basic String", "Hello, 42 Libft!");

    // Test 2: Empty string
    run_strlen_test_case("Empty String", "");

    // Test 3: String with an embedded null (strlen stops at the first null)
    run_strlen_test_case("String with embedded null", "Hello\0World"); 

    // Test 4: Long string
    run_strlen_test_case("Long String", "This is a very very long string that should accurately test the ft_strlen function for performance and correctness over a large data set. It contains many characters and should not cause any segmentation faults or incorrect length calculations.");

    printf("%s=== All ft_strlen manual tests completed successfully! ===%s\n", GREEN, RESET);
    return (EXIT_SUCCESS);
}