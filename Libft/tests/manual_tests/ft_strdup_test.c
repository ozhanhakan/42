#include <stdio.h>   // For printf
#include <stdlib.h>  // For strdup, free
#include <string.h>  // For strcmp, strlen
#include "../../src/libft.h" // Don't forget to include your libft.h here!

// ft_strdup function prototype (if not in libft.h or commented out)
// char    *ft_strdup(const char *s1);

// Helper test function
void test_strdup(const char *original_str, const char *description, int test_num)
{
    char *ft_dup = NULL;
    char *std_dup = NULL;
    int status = 1; // 1 = PASS, 0 = FAIL

    printf("Test %d: %s\n", test_num, description);
    printf("  Original string: \"%s\"\n", original_str);

    // Call our ft_strdup function
    ft_dup = ft_strdup(original_str);
    // Call standard strdup function
    std_dup = strdup(original_str);

    // Check if allocation status is consistent (both NULL or both non-NULL)
    if ((ft_dup == NULL && std_dup != NULL) || (ft_dup != NULL && std_dup == NULL))
    {
        printf("  FAIL: Allocation status differs (ft_dup: %p, std_dup: %p).\n", (void *)ft_dup, (void *)std_dup);
        status = 0;
    }
    else if (ft_dup == NULL && std_dup == NULL)
    {
        printf("  Allocation FAILED for both functions (expected).\n");
        printf("  Status: %s\n\n", status ? "PASS" : "FAIL"); // Still PASS if consistent NULL
        // No need to free if both pointers are NULL.
        return;
    }
    else // Both allocated successfully, now check content and size
    {
        // Check if the content is the same
        if (strcmp(ft_dup, std_dup) != 0)
        {
            printf("  FAIL: Duplicated string content differs.\n");
            printf("    ft_strdup output: \"%s\"\n", ft_dup);
            printf("    strdup output:    \"%s\"\n", std_dup);
            status = 0;
        }
        // Check if the length (including null terminator) is the same
        else if (strlen(ft_dup) != strlen(std_dup)) // Should be same if strcmp is 0, but good for explicit check
        {
             printf("  FAIL: Duplicated string length differs.\n");
             printf("    ft_strdup len: %zu\n", strlen(ft_dup));
             printf("    strdup len:    %zu\n", strlen(std_dup));
             status = 0;
        }
        else
        {
            printf("  Duplicated string content and length match.\n");
        }
    }

    // Print final status
    printf("  Status: %s\n\n", status ? "PASS" : "FAIL");

    // Free allocated memory to prevent leaks
    if (ft_dup)
        free(ft_dup);
    if (std_dup)
        free(std_dup);
}

int main(void)
{
    printf("--- ft_strdup Testleri ---\n\n");

    test_strdup("Hello World!", "Basit bir string kopyalama", 1);
    test_strdup("", "Boş string kopyalama", 2);
    test_strdup("a", "Tek karakterli string kopyalama", 3);
    test_strdup("Lorem ipsum dolor sit amet, consectetur adipiscing elit.", "Uzun bir string kopyalama", 4);
    // NULL string testi (strdup NULL input'ta tanımsız davranış sergileyebilir,
    // ancak bazı implementasyonlar NULL dönebilir. Kendi ft_strdup'un için NULL check yapmıyoruz)
    // test_strdup(NULL, "NULL string kopyalama", 5); // DİKKAT: Bu test, ft_strdup'un NULL girdiyle nasıl davrandığına bağlıdır.
                                                    // Genellikle strdup NULL input'ta tanımsız davranıştır.

    return 0;
}
