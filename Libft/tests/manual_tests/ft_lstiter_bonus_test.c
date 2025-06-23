#include <stdio.h>
#include <ctype.h> // toupper için
#include <stdlib.h>
#include "../../src/libft.h" // Kendi libft.h dosyanı buraya dahil etmeyi unutma!
#include <string.h>

// String'in tüm harflerini büyüten bir fonksiyon
void	string_toupper(void *content)
{
	char *str = (char *)content;
	if (!str)
		return;
	while (*str)
	{
		*str = toupper(*str);
		str++;
	}
}

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
	char *s1 = strdup("merhaba");
	char *s2 = strdup("dünya");

	ft_lstadd_back(&head, ft_lstnew(s1));
	ft_lstadd_back(&head, ft_lstnew(s2));

	printf("ft_lstiter öncesi:\n");
	print_list(head);

	// string_toupper fonksiyonunu her elemana uygulayalım.
	ft_lstiter(head, &string_toupper);

	printf("\nft_lstiter sonrası:\n");
	print_list(head);

	// Belleği temizle
	ft_lstclear(&head, &free);
	return (0);
}
