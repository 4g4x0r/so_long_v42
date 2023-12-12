/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guortun- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 16:36:39 by guortun-          #+#    #+#             */
/*   Updated: 2022/08/09 20:25:03 by guortun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned int	i;
	const char		*c;
	char			*d;

	c = src;
	d = dst;
	i = 0;
	if (c == NULL && d == NULL)
		return (NULL);
	while (i < n)
	{
		d[i] = c[i];
		i++;
	}
	return (d);
}
