#include "libft.h"
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*aux1;
	unsigned char	*aux2;
	size_t			i;
	i = 0;
	aux1 = (unsigned char *)dst;
	aux2 = (unsigned char *)src;
	if (aux1 > aux2)
	{
		while (len--)
			aux1[len] = aux2[len];
	}
	else if (aux1 < aux2)
	{
		while (i < len)
		{
			aux1[i] = aux2[i];
			i++;
		}
	}
	return (dst);
}