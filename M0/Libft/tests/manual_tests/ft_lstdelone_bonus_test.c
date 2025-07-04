#include <stdio.h>
#include <string.h> // strdup
#include <stdlib.h> // free
#include "../../src/libft.h" // Kendi libft.h dosyanı buraya dahil etmeyi unutma!

// Content'i (char *) serbest bırakacak olan fonksiyon
void	del_content(void *content)
{
	printf("del_content çağrıldı, '%s' içeriği siliniyor.\n", (char *)content);
	free(content); // void* pointer'ını free ediyoruz.
}

int	main(void)
{
	t_list	*node_to_delete;
	char	*dynamic_str;

	// Dinamik olarak bir string oluşturalım ki 'del' fonksiyonu anlamlı olsun.
	dynamic_str = strdup("Silinecek Veri");
	if (!dynamic_str)
		return (1);

	// Bu dinamik string ile bir düğüm oluşturalım.
	node_to_delete = ft_lstnew(dynamic_str);
	if (!node_to_delete)
	{
		free(dynamic_str);
		return (1);
	}

	printf("Silinecek düğüm oluşturuldu: content = \"%s\"\n", (char *)node_to_delete->content);

	// ft_lstdelone'ı çağırarak hem content'i hem de düğümü silelim.
	ft_lstdelone(node_to_delete, &del_content);

	printf("Düğüm silindi. Program Valgrind gibi bir araçla kontrol edilirse bellek sızıntısı olmamalıdır.\n");

	// NOT: node_to_delete artık geçersiz bir adresi gösterir.
	// Tekrar erişmeye çalışmak tanımsız davranışa yol açar (Undefined Behavior).
	return (0);
}