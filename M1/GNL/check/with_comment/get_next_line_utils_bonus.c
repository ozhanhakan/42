#include "get_next_line_bonus.h" // Bonus fonksiyon prototipleri ve yardımcılar

// ft_strlen: Bir stringin uzunluğunu döndürür.
// s: Uzunluğu ölçülecek string.
// NULL gelirse 0 döner.
size_t ft_strlen(const char *s)
{
    size_t i = 0;
    while (s && s[i])
        i++;
    return (i);
}

// ft_strchr: Bir karakterin string içinde olup olmadığını bulur.
// s: Aranacak string, c: Aranacak karakter.
// Karakter bulunursa adresini, bulunmazsa NULL döner.
char *ft_strchr(const char *s, int c)
{
    if (!s)
        return (NULL);
    while (*s)
    {
        if (*s == (char)c)
            return ((char *)s);
        s++;
    }
    if (c == 0)
        return ((char *)s);
    return (NULL);
}

// ft_strdup: Bir stringin kopyasını oluşturur.
// s: Kopyalanacak string.
// Yeni ayrılan bellekte kopyasını döndürür.
char *ft_strdup(const char *s)
{
    size_t len = ft_strlen(s);
    char *dup = malloc(len + 1);
    if (!dup)
        return (NULL);
    for (size_t i = 0; i < len; i++)
        dup[i] = s[i];
    dup[len] = '\0';
    return (dup);
}

// ft_strjoin_and_free: İki stringi birleştirir, ilkini serbest bırakır.
// s1: Birleştirilecek ilk string (belleği serbest bırakılır)
// s2: Birleştirilecek ikinci string
// Sonuç olarak yeni birleştirilmiş string döner.
char *ft_strjoin_and_free(char *s1, char *s2)
{
    size_t len1 = ft_strlen(s1);
    size_t len2 = ft_strlen(s2);
    char *res = malloc(len1 + len2 + 1);
    if (!res)
        return (NULL);
    for (size_t i = 0; i < len1; i++)
        res[i] = s1[i];
    for (size_t i = 0; i < len2; i++)
        res[len1 + i] = s2[i];
    res[len1 + len2] = '\0';
    free(s1);
    return (res);
}
