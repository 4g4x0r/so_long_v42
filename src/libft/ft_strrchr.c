/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 11:57:55 by guortun-          #+#    #+#             */
/*   Updated: 2022/07/14 11:59:37 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char		*ultimo;
	char		buscar;
	size_t		i;

	ultimo = (char *)s;
	buscar = (char)c;
	i = ft_strlen(s);
	while (i > 0)
	{
		if (ultimo[i] == buscar)
			return (ultimo + i);
		i--;
	}
	if (ultimo[i] == buscar)
		return (ultimo);
	return (0);
}
