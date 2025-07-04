#include <stdio.h>
#include "../../src/libft.h" // Kendi libft.h dosyanı buraya dahil etmeyi unutma!

void	print_list(t_list *lst); // Yukarıdaki main'den alınabilir
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

	// Önce boş bir listeye eklemeyi deneyelim.
	printf("Boş listeye 'Eleman 1' ekleniyor...\n");
	ft_lstadd_back(&head, ft_lstnew("Eleman 1"));
	print_list(head);

	// Mevcut listeye ekleme yapalım.
	printf("\nListenin sonuna 'Eleman 2' ekleniyor...\n");
	ft_lstadd_back(&head, ft_lstnew("Eleman 2"));
	print_list(head);

	printf("\nListenin sonuna 'Eleman 3' ekleniyor...\n");
	ft_lstadd_back(&head, ft_lstnew("Eleman 3"));
	print_list(head);

	// Belleği temizle
	t_list *tmp;
	while(head)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}

	return (0);
}