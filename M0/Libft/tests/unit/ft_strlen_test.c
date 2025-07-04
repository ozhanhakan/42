#include <string.h> // Original strlen for comparison
#include <stdio.h>
#include "test_utils.h" // Our testing utilities
#include "libft.h"    // Your ft_strlen

// Individual test cases for ft_strlen
// Each returns 0 on success, 1 on failure.
static int test_strlen_basic(void) {
    const char *str = "Hello World!";
    size_t len_orig = strlen(str);
    size_t len_ft = ft_strlen(str);

    report_test_status("Basic string length", len_orig == len_ft);
    return 0;
}

static int test_strlen_empty_string(void) {
    const char *str = "";
    size_t len_orig = strlen(str);
    size_t len_ft = ft_strlen(str);

    report_test_status("Empty string", len_orig == len_ft);
    return 0;
}

static int test_strlen_with_null_in_middle(void) {
    const char *str = "Hello\0World"; // Contains a null byte in the middle
    size_t len_orig = strlen(str); // Should stop at the first null
    size_t len_ft = ft_strlen(str);

    report_test_status("String with null in middle", len_orig == len_ft);
    return 0;
}

static int test_strlen_long_string(void) {
    const char *str = "This is a very long string that should accurately test the ft_strlen function for performance and correctness over a large data set. It contains many characters and should not cause any segmentation faults or incorrect length calculations.";
    size_t len_orig = strlen(str);
    size_t len_ft = ft_strlen(str);

    report_test_status("Long string", len_orig == len_ft);
    return 0;
}

// Main test function for ft_strlen, runs all its individual tests
int ft_strlen_main(void) {
    print_suite_header("ft_strlen Tests");
    test_strlen_basic();
    test_strlen_empty_string();
    test_strlen_with_null_in_middle();
    test_strlen_long_string();
    print_suite_footer("ft_strlen Tests", 1); // If we reach here, all sub-tests passed
    return 0;
}

// Entry point for this specific test binary
int main(void) {
    return ft_strlen_main();
}