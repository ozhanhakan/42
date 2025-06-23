#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../src/libft.h" // Kendi libft.h dosyanı buraya dahil etmeyi unutma!
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Gerekli Diğer libft Fonksiyonları ve t_list yapısı ---
// ft_lstnew, ft_lstadd_back, ft_lstmap, ft_lstclear vb.
// burada olduğunu varsayıyoruz.

// --- YARDIMCI FONKSİYONLAR ---

/*
 * Bu fonksiyon hem orijinal listenin hem de yeni listenin içeriğini
 * silmek için kullanılabilir, çünkü artık ikisi de dinamik olarak
 * (strdup ve malloc ile) oluşturuluyor.
 */
void	del_string_content(void *content)
{
	// Gelen void pointer'ını free edilecek.
	// printf("İçerik siliniyor: %s\n", (char *)content); // Ne silindiğini görmek için
	free(content);
}

// İçeriği kopyalayıp sonuna " - MAPPED" ekleyen fonksiyon
void	*map_add_suffix(void *content)
{
	char	*original;
	char	*new_str;
	char	*suffix;

	original = (char *)content;
	suffix = " - MAPPED";
	// Yeni string için yeterli bellek ayır
	new_str = (char *)malloc(strlen(original) + strlen(suffix) + 1);
	if (!new_str)
		return (NULL);
	strcpy(new_str, original);
	strcat(new_str, suffix);
	return ((void *)new_str);
}

// Listeyi yazdırmak için yardımcı fonksiyon
void	print_list(t_list *lst)
{
	while (lst)
	{
		printf("-> [%s] ", (char *)lst->content);
		lst = lst->next;
	}
	printf("-> NULL\n");
}

// --- ANA TEST FONKSİYONU ---

int	main(void)
{
	t_list	*original_list;
	t_list	*mapped_list;

	original_list = NULL;
	
	// 1. Orijinal listeyi DİNAMİK içerikle oluşturalım.
	// strdup, yeni bellek ayırdığı için içeriği dinamik yapar.
	ft_lstadd_back(&original_list, ft_lstnew(strdup("Birinci eleman")));
	ft_lstadd_back(&original_list, ft_lstnew(strdup("İkinci eleman")));
	ft_lstadd_back(&original_list, ft_lstnew(strdup("Üçüncü eleman")));

	printf("Dinamik içerikli orijinal liste:\n");
	print_list(original_list);

	// 2. ft_lstmap ile yeni bir liste oluşturalım.
	mapped_list = ft_lstmap(original_list, &map_add_suffix, &del_string_content);

	if (mapped_list)
	{
		printf("\n'map' uygulanmış yeni liste:\n");
		print_list(mapped_list);
	}
	else
		printf("\n'map' işlemi başarısız oldu.\n");

	// 3. Her iki listeyi de temizleyelim.
	// Artık her iki listenin içeriği de dinamik olduğu için
	// AYNI silme fonksiyonunu (del_string_content) kullanabiliriz.
	// 'free_dummy' gibi bir fonksiyona gerek kalmadı.
	printf("\nBellek temizleniyor...\n");
	ft_lstclear(&original_list, &del_string_content);
	ft_lstclear(&mapped_list, &del_string_content);

	printf("Orijinal liste temizlendi.\n");
	printf("Yeni liste temizlendi.\n");

	// Valgrind ile kontrol edildiğinde bellek sızıntısı olmamalıdır.
	return (0);
}
