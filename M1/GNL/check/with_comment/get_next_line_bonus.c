#include "get_next_line_bonus.h" // Bonus fonksiyon prototipleri ve yardımcılar

// Her fd için ayrı stash tutan static dizi
static char *stash[MAX_FD]; // MAX_FD: Aynı anda yönetilebilecek maksimum dosya tanımlayıcı sayısı

/*
 * read_to_newline:
 *  - fd'den satır sonuna kadar okur ve okunan verileri biriktirir.
 *  - old_stash: Önceki çağrılardan kalan veri (NULL olabilir).
 *  - Bellek yönetimi ve hata kontrolü içerir.
 */
static char *read_to_newline(int fd, char *old_stash)
{
    char *buf; // Okuma için buffer
    int bytes; // Okunan byte sayısı

    buf = malloc(BUFFER_SIZE + 1); // Okuma için buffer ayır
    if (!buf)
        return (NULL);
    bytes = 1;
    while (bytes > 0 && !ft_strchr(old_stash, '\n')) // Satır sonu bulunana kadar oku
    {
        bytes = read(fd, buf, BUFFER_SIZE); // fd'den BUFFER_SIZE kadar oku
        if (bytes == -1) // Okuma hatası
        {
            free(buf);
            free(old_stash);
            return (NULL);
        }
        buf[bytes] = '\0'; // Okunan veriyi string olarak sonlandır
        old_stash = ft_strjoin_and_free(old_stash, buf); // Okunanı biriktir
    }
    free(buf);
    return (old_stash);
}

/*
 * extract_line:
 *  - Bir satırı (\n dahil) stash'ten ayıklar.
 *  - Bellek yönetimi ve hata kontrolü içerir.
 */
static char *extract_line(char *full_stash)
{
    int i = 0;
    char *line;

    if (!full_stash || !full_stash[0])
        return (NULL);
    while (full_stash[i] && full_stash[i] != '\n')
        i++;
    if (full_stash[i] == '\n')
        i++;
    line = malloc(i + 1);
    if (!line)
        return (NULL);
    for (int j = 0; j < i; j++)
        line[j] = full_stash[j];
    line[i] = '\0';
    return (line);
}

/*
 * update_stash:
 *  - Okunan satırdan sonrasını yeni stash olarak ayıklar.
 *  - Bellek yönetimi ve hata kontrolü içerir.
 */
static char *update_stash(char *full_stash)
{
    int i = 0, j = 0;
    char *new_stash;

    while (full_stash[i] && full_stash[i] != '\n')
        i++;
    if (!full_stash[i])
    {
        free(full_stash);
        return (NULL);
    }
    i++;
    new_stash = malloc(ft_strlen(full_stash + i) + 1);
    if (!new_stash)
        return (NULL);
    while (full_stash[i])
        new_stash[j++] = full_stash[i++];
    new_stash[j] = '\0';
    free(full_stash);
    return (new_stash);
}

/*
 * get_next_line:
 *  - fd'den bir satır okur ve döndürür.
 *  - static char *stash[MAX_FD]: Her fd için ayrı okuma durumu saklar.
 *  - Her çağrıda bir satır döndürür, EOF veya hata durumunda NULL döner.
 */
char *get_next_line(int fd)
{
    char *line;

    if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
        return (NULL);
    stash[fd] = read_to_newline(fd, stash[fd]);
    if (!stash[fd])
        return (NULL);
    line = extract_line(stash[fd]);
    stash[fd] = update_stash(stash[fd]);
    return (line);
}
