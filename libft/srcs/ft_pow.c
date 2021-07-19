#include "libft.h"

int	ft_pow(int nbr, int pow)
{
	int	rs;

	rs = 1;
	if (pow <= 0)
		return (1);
	while (pow--)
		rs = rs * nbr;
	return (rs);
}
