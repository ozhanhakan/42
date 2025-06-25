#include "../src/libft.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>

void	test_ft_isalpha(void)
{
	printf("ft_isalpha test: ");
	if (ft_isalpha('a') &&
		ft_isalpha('Z') &&
		!ft_isalpha('o'))
		printf("OK\n");
	else
		printf("FAIL\n");
}

void	test_ft_isdigit(void)
{
	printf("ft_isdigit test: ");
	if (ft_isdigit('0') &&
		ft_isdigit('1') &&
		!ft_isdigit(' '))
		printf("OK\n");
	else
		printf("FAIL\n");
}

void	test_ft_isalnum(void)
{
	printf("ft_isalnum test: ");
	if (ft_isalnum('0') &&
		ft_isalnum('k') &&
		!ft_isalnum(' '))
		printf("OK\n");
	else
		printf("FAIL\n");
}

void	test_ft_isascii(void)
{
	printf("ft_isascii test: ");
	if (ft_isascii('\0') &&
		ft_isascii(' ') &&
		!ft_isascii(128))
		printf("OK\n");
	else
		printf("FAIL\n");
}

void	test_ft_isprint(void)
{
	printf("ft_isprint test: ");
	if (!ft_isprint(1) &&
		!ft_isprint(127) &&
		ft_isprint(125))
		printf("OK\n");
	else
		printf("FAIL\n");
}

void	test_ft_strlen(void)
{
	printf("ft_strlen test: ");
	if (ft_strlen("test") == 4 &&
		ft_strlen("") == 0)
		printf("OK\n");
	else
		printf("FAIL\n");
}

void	test_ft_memset(void)
{
	printf("ft_memset test: ");
	char buf[5] = "test";
	ft_memset(buf, 'A', 3);
	if (strcmp(buf, "AAAt") == 0 &&
		buf[2] == 'A')
		printf("OK\n");
	else
		printf("FAIL\n");
	
	int nums [] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
	printf("\nint nums dizisi\n");
	for(int i=0; i<3; i++)
		printf("%X, ", nums[i]);
	ft_memset(nums,0x00,  sizeof(int)*2); //sizeof(int) *
	printf("\nmemset sonrası int nums dizisi\n");
	for(int i=0; i<3; i++)
		printf("%X, ", nums[i]);
}

void	test_ft_bzero(void)
{
	printf("ft_bzero test: ");
	char	buf[]="test";
	ft_bzero(buf, 3);
	if (buf[0] == 0 && buf[1] == 0 && buf[2]==0 && buf[3]=='t')
		printf("OK\n");
	else
		printf("FAIL\n");
	
	int nums [] = {0xFFFF, 0xFFFF, 0xFFFF};
	printf("\nint nums dizisi\n");
	for(int i=0; i<3; i++)
		printf("%X, ", nums[i]);
	ft_bzero(nums, 1); //sizeof(int) *
	printf("\nbzero sonrası int nums dizisi\n");
	for(int i=0; i<3; i++)
		printf("%X, ", nums[i]);
}

void	test_ft_memcpy(void)
{
	printf("ft_memcpy test: ");
	char	src[5] = "test";
	char	dest[5] = "";
	ft_memcpy(dest, src, 5);
	if (ft_strncmp(dest, "test", 4) == 0)
		printf("OK\n");
	else
		printf("FAIL\n");
	
	int nums [] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
	int numbs[3] = {0};
	printf("\nint nums dizisi\n");
	for(int i=0; i<3; i++)
		printf("%X, ", nums[i]);
	printf("\nint numbs dizisi\n");
	for(int i=0; i<3; i++)
		printf("%X, ", numbs[i]);
	ft_memcpy(numbs, nums, 1); //sizeof(int) *
	printf("\nbzero sonrası int nums dizisi\n");
	for(int i=0; i<3; i++)
		printf("%X, ", numbs[i]);
}

void	test_ft_memmove(void)
{
	printf("ft_memmove test: ");
	char	buf[10] = "abcdef";
	ft_memmove(buf + 2, buf, 3);
	if (ft_strncmp(buf, "ababc",5) == 0)
		printf("OK\n");
	else
		printf("FAIL\n");
}

void	test_ft_strlcpy(void)
{
	printf("ft_strlcpy test: ");
	char	dest[5]="";
	size_t ret = ft_strlcpy(dest, "test", 6);
	if (ft_strncmp(dest, "test", ft_strlen("test")) == 0 && ret == 4)
		printf("OK\n");
	else
		printf("FAIL\n");
}

void	test_ft_strlcat(void)
{
	printf("ft_strlcat test: ");
	char	dst[10] = "ab";
	size_t ret = ft_strlcat(dst, "cd", 5);
	if (strcmp(dst, "abcd") == 0 && ret == 4)
		printf("OK\n");
	else
		printf("FAIL\n");
	
	printf("ft_strlcat test 2: ");
	char dst2[10] = "ab";
	ret = ft_strlcat(dst2, "cd", 2);
	if (strcmp(dst2, "abcd") == 0 && ret == 4)
		printf("OK\n");
	else
		printf("FAIL\n");
}

void	test_ft_toupper(void)
{
	printf("ft_toupper test: ");
	if (ft_toupper('a') == 'A' && ft_toupper('*')=='*')
		printf("OK\n");
	else
		printf("FAIL\n");
}

void	test_ft_tolower(void)
{
	printf("ft_tolower test: ");
	if (ft_tolower('A') == 'a' && ft_tolower('z')=='z')
		printf("OK\n");
	else
		printf("FAIL\n");
}

void	test_ft_strchr(void)
{
	printf("ft_strchr test: ");
	char	*s = "test";
	if (ft_strchr(s, 'e') == s + 1 && ft_strchr(s, 'x') == NULL)
		printf("OK\n");
	else
		printf("FAIL\n");
}

void	test_ft_strrchr(void)
{
	printf("ft_strrchr test: ");
	char	*s = "testest";
	if (ft_strrchr(s, 'e') == s + 4 && ft_strrchr(s, 'x') == NULL)
		printf("OK\n");
	else
		printf("FAIL\n");
}

void	test_ft_strncmp(void)
{
	printf("ft_strncmp test: ");
	if(ft_strncmp("test", "tes",3) == 0 && 
		ft_strncmp("test", "tesz", 4) < 0)
		printf("OK\n");
	else
		printf("FAIL\n");
}

void	test_ft_memchr(void)
{
	printf("ft_memchr test: ");
	char	s[]= "test";
	if(ft_memchr(s, 'e', 4) == s + 1 && ft_memchr(s, 'x', 4) == NULL)
		printf("OK\n");
	else
		printf("FAIL\n");
}

void	test_ft_memcmp(void)
{
	printf("ft_memcmp test: ");
	char	s1[] = "test";
	char	s2[] = "tesz";
	if (ft_memcmp(s1, s2, 3) == 0 && ft_memcmp(s1, s2, 4) < 0)
		printf("OK\n");
	else
		printf("FAIL\n");
}

void	test_ft_strnstr(void)
{
	printf("ft_strnstr test: ");
	char	*big = "hello world";
	if (ft_strnstr(big, "world", 11) == big + 6 &&
		ft_strnstr(big, "xyz", 11) == NULL)
		printf("OK\n");
	else
		printf("FAIL\n");
}

void	test_ft_atoi(void)
{
	printf("ft_atoi test: ");
	if (ft_atoi("123") == 123 && ft_atoi("-123") == -123)
		printf("OK\n");
	else
		printf("FAIL\n");
}

void	test_ft_calloc(void)
{
	printf("ft_calloc test: ");
	int *p = ft_calloc(3, sizeof(int));
	if (p[0] == 0 && p[1] == 0 && p[2]==0)
		printf("OK\n");
	else
		printf("FAIL\n");
}

void	test_ft_strdup(void)
{
	printf("ft_strdup test: ");
	char *s = ft_strdup("test");
	if (strcmp(s, "test") == 0)
		printf("OK\n");
	else
		printf("FAIL\n");
}

void	test_ft_substr(void)
{
	printf("ft_substr test: ");
	char	*s = ft_substr("test", 1, 2);
	if (strcmp(s, "es") == 0)
		printf("OK\n");
	else
		printf("FAIL\n");
}
void	test_ft_strjoin(void)
{
	printf("strjoin test: ");
	char *s = ft_strjoin("abc", "def");
	printf("%s",strcmp(s, "abcdef") == 0 ? "OK\n" : "FAIL\n");
}

void	test_ft_strtrim(char *str, char *c)
{
	printf("ft_strtrim test: ");
	char	*s = ft_strtrim(str, c); 
	//terminalden ./a.out "**a*b*c**" "*" girince sonuc: a*b*c olmalı
	if (strcmp(s, "a*b*c") == 0)
		printf("OK\n");
	else
		printf("FAIL\n");
}

void	test_ft_split(char *argv, char c)
{
	printf("ft_split test: ");
	char	**arr = ft_split("a,b,c", ',');
	if (strcmp(arr[0], "a") == 0 && strcmp(arr[1], "b") == 0 &&
		strcmp(arr[2], "c") == 0 && arr[3] == NULL)
		printf("OK\n");
	else
		printf("FAIL\n");
	for(int i = 0; arr[i]; i++)
		free(arr[i]);
	free(arr);

	printf("ft_split test-2: ");
	//terminalden ./a.out "a,b,c" "," girince sonuc: OK olmalı
	char	**arr1 = ft_split(argv, c); 
	if (strcmp(arr1[0], "a") == 0 && strcmp(arr1[1], "b") == 0 &&
		strcmp(arr1[2], "c") == 0 && arr1[3] == NULL)
		printf("OK\n");
	else
		printf("FAIL\n");

	  // arr1'i yazdır ve serbest bırak (pointer'ı kaybetmeden)
	for(int i = 0; arr1[i]; i++)
	{
		printf("%s\n", arr1[i]);
		free(arr1[i]);
	}
	free(arr1);
}

void	test_ft_itoa(void)
{
	printf("ft_itoa test: ");
	char	*s = ft_itoa(123);
	if (strcmp(s, "123") == 0)
		printf("OK\n");
	else
		printf("FAIL\n");
	free(s);
}

static char	test_ft_strmapi_f(unsigned int i, char c)
{
	if (i % 2 == 0)
		return ((char)(ft_toupper((int)c)));
	return (c);
}


void	test_ft_strmapi(void)
{
	printf("ft_strmapi test: ");
	char *s = ft_strmapi("abc", test_ft_strmapi_f);
	if(strcmp(s, "AbC") == 0)
		printf("OK\n");
	else
		printf("FAIL\n");
	free(s);
}


static void	test_ft_striteri_f(unsigned int i, char *c_ptr)
{
	 if (i % 2 == 0) // Çift indeks
    {
        if (*c_ptr >= 'a' && *c_ptr <= 'z')
            *c_ptr -= 32;
    }
}

void test_ft_striteri(void) {
    printf("ft_striteri test: ");
    char s[] = "abc";
    ft_striteri(s, test_ft_striteri_f);
    if (strcmp(s, "AbC") == 0) 
        printf("OK\n");
    else 
        printf("FAIL\n");
}

void	test_ft_putchar_fd(void)
{
	printf("ft_putchar test: ");
	int	fd = open("putchar_test.txt",
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Dosya açma hatası");
		return ;
	}
	ft_putchar_fd('Z', fd);
	close(fd);

	fd = open("putchar_test.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("open() Dosya açma hatası");
		return ;
	}
	char buf[2];
	read(fd, buf, 1);
	buf[1] = '\0';
	printf("Dosya içeriği: %s( beklenen: Z)\n", buf);
	close(fd);
}

void	test_ft_putstr_fd(void)
{
	printf("ft_putstr test: ");
	printf("standart output çıktısı: \n");
	ft_putstr_fd("Merhaba 42", 1);

	printf("error output çıktısı: \n");
	ft_putstr_fd("Hello 42\n", 2);

	int fd = open("putstr_test.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ft_putstr_fd("Libft projesi", fd);
	close(fd);
}

void	test_ft_putendl_fd(void)
{
	printf("ft_putendl test: ");
	int fd = open("putendl_test.txt", O_WRONLY | O_APPEND);
	if(fd == -1) // EOF = -1
	{
		perror("open() dosya açma hatası");
		return ;
	}
	ft_putendl_fd("putendl_fd", fd);
	close(fd);
}

void	test_ft_putnbr_fd(void)
{
	printf("ft_putnbr test: ");
	int fd = open("putnbr_test.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("open() dosya açma hatası");
		return ;
	}
	ft_putnbr_fd(42, fd);
	close(fd);
}
void	test_ft_lstnew2(void)
{
	printf("ft_lstnew test: ");
	char *content = "new content";
	t_list *new_node = ft_lstnew(content);
	printf("%s", new_node->content == content && new_node->next == NULL ? "OK" : "FAIL");
}

void	test_ft_lstadd_front(void)
{
	printf("ft_lstadd_front test: ");
	t_list *lst = NULL;
	t_list	*node = ft_lstnew("a");
	ft_lstadd_front(&lst, node);
	if(lst == node && lst->next ==  NULL)
		printf("ok");
	else
		printf("FAIL");
}
void test_ft_lstsize(void) {
    printf("ft_lstsize test: ");
    t_list *lst = ft_lstnew("a");
    lst->next = ft_lstnew("b");
    if (ft_lstsize(lst) == 2) 
        printf("OK\n");
    else 
        printf("FAIL\n");
    free(lst->next);
    free(lst);
}

void test_ft_lstlast(void) {
    printf("ft_lstlast test: ");
    t_list *lst = ft_lstnew("a");
    t_list *last = ft_lstnew("b");
    lst->next = last;
    if (ft_lstlast(lst) == last) 
        printf("OK\n");
    else 
        printf("FAIL\n");
    free(last);
    free(lst);
}

void test_ft_lstadd_back(void) {
    printf("ft_lstadd_back test: ");
    t_list *lst = ft_lstnew("a");
    t_list *node = ft_lstnew("b");
    ft_lstadd_back(&lst, node);
    if (ft_lstlast(lst) == node) 
        printf("OK\n");
    else 
        printf("FAIL\n");
    free(node);
    free(lst);
}

void test_ft_lstdelone(void) {
    printf("ft_lstdelone test: ");
    char *content = strdup("test");
    t_list *node = ft_lstnew(content);
    ft_lstdelone(node, free);
    printf("OK\n"); /* Bellek serbest bırakıldı, manuel kontrol gerekir */
}

void test_ft_lstclear(void) {
    printf("ft_lstclear test: ");
    t_list *lst = ft_lstnew(strdup("a"));
    lst->next = ft_lstnew(strdup("b"));
    ft_lstclear(&lst, free);
    if (lst == NULL) 
        printf("OK\n");
    else 
        printf("FAIL\n");
}

void test_ft_lstiter(void) {
    printf("ft_lstiter test: ");
    t_list *lst = ft_lstnew(strdup("a"));
    lst->next = ft_lstnew(strdup("b"));
    ft_lstiter(lst, (void (*)(void*))ft_putstr_fd);
    printf("\nOK\n"); /* Çıktıyı manuel kontrol edin */
    ft_lstclear(&lst, free);
}

void test_ft_lstmap(void) {
    printf("ft_lstmap test: ");
    t_list *lst = ft_lstnew(strdup("a"));
    t_list *new = ft_lstmap(lst, (void *(*)(void*))ft_strdup, free);
    if (strcmp(new->content, "a") == 0) 
        printf("OK\n");
    else 
        printf("FAIL\n");
    ft_lstclear(&lst, free);
    ft_lstclear(&new, free);
}

static char ft_h_strmap(unsigned int ui, char c)
{
	if(ft_isdigit(c) && ui != -1)
		return ('*');
	return (c);
}
// Bonus Parts
/*lstdelone lstclear lstmap için silme fonksiyonu*/
static void del_content( void *content)
{
	free(content);
}
/*list iter için içerik yazıdrma fonksiyonu*/
static void print_content(void *content)
{
	if(content)
		ft_putstr_fd((char *)content, 1);
}

/*lstmap için içerik kopyalama fonksiyonu*/
static void	*duplicate_content(void *content)
{
	if(!content)
		return (NULL);
	return (ft_strdup((char *)content));
}
/*Test Fonksiyonları*/
static void	test_ft_lstnew(void)
{
	char *content = "text";
	t_list *node = ft_lstnew(content);

	printf("ft_lstnew test: %s\n",
	node && node->content == content && node->next == NULL ?
	"OK\n" :
	"FAIL\n");
}

int	main( int argc, char *argv[])
{
	printf("argc: %d, argv[0]: %s, argv[1]: %s\n", argc, argv[0], argv[1]);
	// Part-1
	// test_ft_isalpha();
	// test_ft_isdigit();
	// test_ft_isalnum();
	// test_ft_isascii();
	// test_ft_isprint();
	// test_ft_strlen();
	// test_ft_memset();
	// test_ft_bzero();
	// test_ft_memcpy();
	// test_ft_memmove();
	// test_ft_strlcpy();
	// test_ft_strlcat();
	// test_ft_toupper();
	// test_ft_tolower();
	// test_ft_strchr();
	// test_ft_strrchr();
	// test_ft_strncmp();
	// test_ft_memchr();
	// test_ft_memcmp();
	// test_ft_strnstr();
	// test_ft_atoi();
	// test_ft_calloc();
	// test_ft_strdup();

	// Part-2
	// test_ft_substr();
	// test_ft_strjoin();
	// test_ft_strtrim(argv[1], argv[2]);
	// test_ft_split(argv[1], argv[2][0]);
	// test_ft_itoa();
	// test_ft_strmapi();
	// test_ft_striteri();
	// test_ft_putchar_fd();
	// test_ft_putstr_fd();
	// test_ft_putendl_fd();
	//test_ft_putnbr_fd();

	// Bonus
	// test_ft_lstnew();
	// char s[100]= "burak bugun okula geldi";
	// char **s1 = ft_split(s,' ');
	// int i = 0
	// printf("%s", s1[0]);
	//ft_Strmapi
	// char	test[]="abc123def";
	// char *newtest = ft_strmapi(test, ft_h_strmap);
	// printf("%s", newtest);

	return (0);
}

