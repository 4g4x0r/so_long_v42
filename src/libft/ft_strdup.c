#include "libft.h"
char	*ft_strdup(const char	*s1)
{
	char	*aux;
	size_t	i;
	i = 0;
	aux = ft_calloc (sizeof(char) * ft_strlen(s1) + 1, 1);
	if (aux == NULL)
		return (NULL);
	while (s1[i])
	{
		aux[i] = s1[i];
		i++;
	}
	return (aux);
}