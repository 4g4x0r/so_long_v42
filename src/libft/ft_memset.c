#include <stdio.h>
void	*ft_memset(void *b, int c, size_t len)
{
	unsigned int	i;
	unsigned char	*src;
	src = b;
	i = 0;
	while (i < len)
	{
		src[i] = c;
		i++;
	}
	return (b);
}