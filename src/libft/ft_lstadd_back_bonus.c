/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 19:20:05 by guortun-          #+#    #+#             */
/*   Updated: 2022/08/18 19:20:07 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
