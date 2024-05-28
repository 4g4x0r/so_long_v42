#include "libft.h"
void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*back;
	back = *alst;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	if (!new)
		return ;
	while (back && back->next)
		back = back->next;
	back->next = new;
}