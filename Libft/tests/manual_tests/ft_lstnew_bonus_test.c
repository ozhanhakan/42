#include <stdio.h> // printf için
#include <string.h> // strdup için (dinamik bellek ayırır)
#include "../../src/libft.h" // Kendi libft.h dosyanı buraya dahil etmeyi unutma!

int	main(void)
{
	char	*str_content = strdup("Merhaba 42!");
	t_list	*new_element;

	// str_content için bellek ayrılamadıysa programı sonlandır
	if (!str_content)
		return (1);
	
	printf("'%s' içeriği ile yeni bir düğüm oluşturuluyor...\n", str_content);

	// ft_lstnew fonksiyonu ile yeni bir düğüm oluşturulur.
	new_element = ft_lstnew(str_content);

	if (new_element)
	{
		printf("Düğüm başarıyla oluşturuldu.\n");
		// Düğümün içeriğini ve next işaretçisini kontrol edelim.
		// content'i string'e cast ederek yazdırıyoruz.
		printf("Düğümün içeriği (content): %s\n", (char *)new_element->content);
		// next'in NULL olup olmadığını kontrol ediyoruz.
		if (new_element->next == NULL)
			printf("Düğümün 'next' işaretçisi doğru bir şekilde NULL.\n");
		else
			printf("HATA: 'next' işaretçisi NULL olmalıydı!\n");
		
		// Test için ayrılan belleği temizliyoruz.
		free(new_element->content); // strdup ile ayrılan bellek
		free(new_element); // ft_lstnew içinde ayrılan bellek
	}
	else
	{
		printf("HATA: Düğüm oluşturulamadı (malloc başarısız oldu).\n");
	}
	return (0);
}
