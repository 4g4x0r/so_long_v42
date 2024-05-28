#include "libft.h"
int	ft_isalnum(int str)
{
	if ((str > 96 && str < 123) || (str > 64 && str < 91)
		|| (str > 47 && str < 58))
		return (1);
	else
		return (0);
}