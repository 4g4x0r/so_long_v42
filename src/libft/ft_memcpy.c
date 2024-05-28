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