#include "libft.h"
char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;
	i = 0;
	j = 0;
	while (dest[i] != 0)
	{
		i++;
	}
	while (src[j] != 0)
	{
		dest[i + j] = src[j];
		j++;
	}
	dest [i + j] = '\0';
	return (dest);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*aux1;
	char	*aux2;
	char	*con;
	size_t	i;
	size_t	j;
	if (!s1)
		return (NULL);
	i = 0;
	j = ft_strlen(s1) + ft_strlen(s2);
	aux1 = (char *)s1;
	aux2 = (char *)s2;
	con = ft_calloc((sizeof(char) * j + 1), 1);
	if (!con)
		return (NULL);
	while (aux1[i])
	{
		con[i] = aux1[i];
		i++;
	}
	ft_strcat(con, aux2);
	return (con);
}