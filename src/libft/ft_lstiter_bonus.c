#include "libft.h"
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*lst_aux;
	while (lst != NULL)
	{
		lst_aux = lst->next;
		f(lst->content);
		lst = lst_aux;
	}
}