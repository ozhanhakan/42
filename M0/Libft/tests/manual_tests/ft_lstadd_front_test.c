#include <stdio.h>
#include "../../src/libft.h" // Kendi libft.h dosyanı buraya dahil etmeyi unutma!


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

int	main(void)
{
	t_list	*head = NULL;
	t_list	*node1;
	t_list	*node2;

	// İki yeni düğüm oluşturalım.
	node1 = ft_lstnew("Dünya!");
	node2 = ft_lstnew("Merhaba");

	printf("Başlangıçta liste boş.\n");
	print_list(head);

	// İlk düğümü listenin başına ekleyelim. Liste: "Dünya!" -> NULL
	ft_lstadd_front(&head, node1);
	printf("\n'Dünya!' eklendi.\n");
	print_list(head);

	// İkinci düğümü listenin başına ekleyelim. Liste: "Merhaba" -> "Dünya!" -> NULL
	ft_lstadd_front(&head, node2);
	printf("\n'Merhaba' eklendi.\n");
	print_list(head);

	// Belleği temizle
	free(node1);
	free(node2);
	return (0);
}