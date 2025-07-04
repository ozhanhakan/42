#include <stdio.h>
#include "../../src/libft.h" // Kendi libft.h dosyanı buraya dahil etmeyi unutma!
#include <string.h>

int main(void)
{
	t_list *head = NULL;
	
	head = ft_lstnew("İlk");
	head->next = ft_lstnew("Orta");
	head->next->next = ft_lstnew("Son");

	printf("Liste: \"İlk\" -> \"Orta\" -> \"Son\"\n");
	
	// Listenin son elemanını bulalım.
	t_list *last_node = ft_lstlast(head);

	if (last_node)
	{
		printf("ft_lstlast ile bulunan son eleman: \"%s\"\n", (char *)last_node->content);
		if (strcmp((char *)last_node->content, "Son") == 0)
			printf("Test başarılı!\n");
		else
			printf("Test başarısız!\n");
	}
	else
	{
		printf("HATA: Son eleman bulunamadı.\n");
	}

	// Belleği temizle
	free(head->next->next);
	free(head->next);
	free(head);
	return (0);
}