/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 11:46:42 by guortun-          #+#    #+#             */
/*   Updated: 2022/07/14 11:47:53 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	c;

	c = 0;
	while (c < n)
	{
		if (*(unsigned char *)(s1 + c) != *(unsigned char *)(s2 + c))
			return (*(unsigned char *)(s1 + c) - *(unsigned char *)(s2 + c));
		c++;
	}
	return (0);
}
