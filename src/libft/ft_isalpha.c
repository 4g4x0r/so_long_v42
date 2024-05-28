#include "libft.h" 
int	ft_isalpha(int c)
{
	if (((c >= 'a') && (c <= 'z')) || ((c >= 65) && (c <= 90)))
		return (1);
	return (0);
}