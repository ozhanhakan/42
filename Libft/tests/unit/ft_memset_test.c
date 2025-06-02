#include <string.h> // Original memset for comparison
#include <stdio.h>
#include "test_utils.h" // Our testing utilities
#include "libft.h"    // Your ft_memset

// Pragma for specific compiler warnings (if needed for testing original functions)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmemset-transposed-args"

// All individual test cases for ft_memset
// Each returns 0 on success, 1 on failure.
static int test_memset_basic_fill(void) {
    char s1[21]; // "abcdefghijklmnopqrst" (20 chars) + \0 = 21 bytes
    char s2[21];
    
    strcpy(s1, "abcdefghijklmnopqrst");
    strcpy(s2, "abcdefghijklmnopqrst");

    memset(s1, 'X', 10);
    ft_memset(s2, 'X', 10);

    report_test_status("Basic fill", check_memory_equality(s1, s2, 21, "Buffer content after basic fill"));
    return 0; // If report_test_status didn't exit, it's a pass
}

static int test_memset_full_array(void) {
    char s1[11]; // "0123456789" (10 chars) + \0 = 11 bytes
    char s2[11];
    
    strcpy(s1, "0123456789");
    strcpy(s2, "0123456789");

    memset(s1, 'Z', 10);
    ft_memset(s2, 'Z', 10);

    report_test_status("Full array fill", check_memory_equality(s1, s2, 11, "Buffer content after full array fill"));
    return 0;
}

static int test_memset_zero_fill(void) {
    char s1[16]; // "test string 123" (15 chars) + \0 = 16 bytes
    char s2[16];
    
    strcpy(s1, "test string 123");
    strcpy(s2, "test string 123");

    memset(s1, 0, 8);
    ft_memset(s2, 0, 8);

    report_test_status("Zero fill", check_memory_equality(s1, s2, 16, "Buffer content after zero fill"));
    return 0;
}

static int test_memset_size_zero(void) {
    char s1[6]; // "abcde" (5 chars) + \0 = 6 bytes
    char s2[6];
    
    strcpy(s1, "abcde");
    strcpy(s2, "abcde");

    char *ret_s1 = (char *)memset(s1, 'Y', 0);
    char *ret_s2 = (char *)ft_memset(s2, 'Y', 0);

    // Check return values and ensure content didn't change (as size is 0)
    int success = (ret_s1 == s1 && ret_s2 == s2 && check_memory_equality(s1, (const void*)"abcde\0", 6, "Content unchanged with size 0"));
    report_test_status("Size zero and return value", success);
    return 0;
}

static int test_memset_return_value(void) {
    char s[10];
    char *ret_ft = (char *)ft_memset(s, 'A', 5);
    
    report_test_status("Return value check", ret_ft == s);
    return 0;
}

// Restore previous diagnostic settings
#pragma GCC diagnostic pop

// Main test function for ft_memset, runs all its individual tests
int ft_memset_main(void) {
    print_suite_header("ft_memset Tests");
    test_memset_basic_fill();
    test_memset_full_array();
    test_memset_zero_fill();
    test_memset_size_zero();
    test_memset_return_value();
    print_suite_footer("ft_memset Tests", 1); // If we reach here, all sub-tests passed
    return 0;
}

// Entry point for this specific test binary
int main(void) {
    return ft_memset_main();
}