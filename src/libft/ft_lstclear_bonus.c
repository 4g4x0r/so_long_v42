/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 19:19:30 by guortun-          #+#    #+#             */
/*   Updated: 2022/08/18 19:19:32 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*lst_aux;
	t_list	*save;

	if (*lst != NULL)
	{
		lst_aux = *lst;
		while (lst_aux != NULL)
		{
			save = lst_aux->next;
			del(lst_aux->content);
			free(lst_aux);
			lst_aux = save;
		}
		*lst = NULL;
	}
}
