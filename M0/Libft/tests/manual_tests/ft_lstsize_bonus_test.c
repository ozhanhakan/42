#include <stdio.h>
#include "../../src/libft.h" // Kendi libft.h dosyanı buraya dahil etmeyi unutma!

int main(void)
{
	t_list *head = NULL;
	
	// Üç elemanlı bir liste oluşturalım
	head = ft_lstnew("Eleman 3");
	ft_lstadd_front(&head, ft_lstnew("Eleman 2"));
	ft_lstadd_front(&head, ft_lstnew("Eleman 1"));

	printf("Liste oluşturuldu. Boyut hesaplanıyor...\n");
	
	// ft_lstsize ile boyutunu hesaplayıp yazdıralım.
	int size = ft_lstsize(head);
	printf("Listenin boyutu: %d\n", size);

	if (size == 3)
		printf("Test başarılı!\n");
	else
		printf("Test başarısız! Beklenen: 3, Gelen: %d\n", size);

	// Belleği temizle (basit test için manuel temizlik)
	t_list *tmp;
	while(head)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}
	return (0);
}
