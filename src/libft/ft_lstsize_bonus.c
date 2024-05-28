#include "libft.h"
int	ft_lstsize(t_list *lst)
{
	int	size;
	size = 0;
	if (lst != NULL)
	{
		while (lst->next != NULL)
		{
			lst = lst->next;
			size++;
		}
		size++;
	}
	return (size);
}