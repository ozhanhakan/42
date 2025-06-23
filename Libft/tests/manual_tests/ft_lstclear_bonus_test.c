#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../src/libft.h" // Kendi libft.h dosyanı buraya dahil etmeyi unutma!

void	del_content(void *content); // Yukarıdaki main'den alınabilir
// Content'i (char *) serbest bırakacak olan fonksiyon
void	del_content(void *content)
{
	printf("del_content çağrıldı, '%s' içeriği siliniyor.\n", (char *)content);
	free(content); // void* pointer'ını free ediyoruz.
}

void	print_list(t_list *lst);  // Yukarıdaki main'den alınabilir
void	print_list(t_list *lst)
{
	printf("Liste içeriği: ");
	while (lst)
	{
		printf("\"%s\" -> ", (char *)lst->content);
		lst = lst->next;
	}
	printf("NULL\n");
}

int main(void)
{
	t_list *head = NULL;

	// strdup kullanarak dinamik içerikli bir liste oluşturalım.
	ft_lstadd_back(&head, ft_lstnew(strdup("Bir")));
	ft_lstadd_back(&head, ft_lstnew(strdup("İki")));
	ft_lstadd_back(&head, ft_lstnew(strdup("Üç")));

	printf("Temizlemeden önce liste:\n");
	print_list(head);

	// ft_lstclear ile tüm listeyi temizleyelim.
	printf("\nListe temizleniyor...\n");
	ft_lstclear(&head, &del_content);

	printf("\nListe temizlendi. 'head' işaretçisi kontrol ediliyor...\n");
	if (head == NULL)
	{
		printf("Test başarılı: 'head' şimdi NULL.\n");
	}
	else
	{
		printf("Test başarısız: 'head' NULL olmalıydı!\n");
	}

	return (0);
}