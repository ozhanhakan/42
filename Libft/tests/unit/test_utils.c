#include "test_utils.h"

// Test sonucu raporlama
void report_test_status(const char *test_name, int success) {
    if (success) {
        printf("%s  [OK] %s%s\n", GREEN_COLOR, test_name, RESET_COLOR);
    } else {
        printf("%s  [FAIL] %s%s\n", RED_COLOR, test_name, RESET_COLOR);
        exit(EXIT_FAILURE); // Herhangi bir test başarısız olursa hemen çık
    }
}

// Bellek eşitliğini kontrol etme
int check_memory_equality(const void *s1, const void *s2, size_t n, const char *message) {
    if (memcmp(s1, s2, n) != 0) {
        printf("%s    FAIL: %s - Memory mismatch%s\n", RED_COLOR, message, RESET_COLOR);
        // Debugging için: Hata anında bellek içeriğini basabiliriz
        // printf("      Expected: ");
        // for (size_t i = 0; i < n; i++) printf("%02x ", ((unsigned char*)s2)[i]);
        // printf("\n      Got:      ");
        // for (size_t i = 0; i < n; i++) printf("%02x ", ((unsigned char*)s1)[i]);
        // printf("\n");
        return 0; // Başarısız
    }
    return 1; // Başarılı
}

// Test suitini çalıştırma
void run_test_suite(int (*test_func)(), const char *test_func_name) {
    printf("%sRunning %s...%s\n", YELLOW_COLOR, test_func_name, RESET_COLOR);
    int overall_success = test_func(); // Test fonksiyonunu çağır

    if (overall_success == 0) {
        printf("%s✓ %s PASSED%s\n\n", GREEN_COLOR, test_func_name, RESET_COLOR);
    } else {
        printf("%s✗ %s FAILED%s\n\n", RED_COLOR, test_func_name, RESET_COLOR);
        exit(EXIT_FAILURE); // Test suit başarısız olursa çık
    }
}

// Suite başlığı basma
void print_suite_header(const char *suite_name) {
    printf("\n%s=== %s ===%s\n", YELLOW_COLOR, suite_name, RESET_COLOR);
}

// Suite sonu raporlama
void print_suite_footer(const char *suite_name, int success) {
    // BURADAKİ HATAYI DÜZELTTİK: SON `%s` EKLEDİK
    printf("%s--- %s %s ---%s\n", YELLOW_COLOR, suite_name, (success ? "COMPLETED" : "FAILED"), RESET_COLOR);
}