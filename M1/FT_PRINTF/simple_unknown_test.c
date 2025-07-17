#include <stdio.h>

int main()
{
    printf("Standard printf behavior:\n");
    printf("printf(\"%%q\") = ");
    int ret = printf("%q");
    printf(" [return value: %d]\n", ret);
    
    printf("printf(\"%%z\") = ");
    ret = printf("%z");
    printf(" [return value: %d]\n", ret);
    
    return 0;
}
