#include "libft.h"

static int	base_len(char *base)
{
	int	i;

	i = 0;
	while (base[i])
		i++;
	return (i);
}

static int	check_base(char *base)
{
	int	i;
	int	n;

	i = 0;
	if (base[0] == '\0' || base[1] == '\0')
		return (0);
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		n = 1;
		while (base[i + n])
		{
			if (base[i] == base[i + n])
				return (0);
			n++;
		}
		i++;
	}
	return (1);
}

void	ft_putnbr_base(int nbr, char *base)
{
	long int	n;

	n = nbr;
	if (check_base(base))
	{
		if (n < 0)
		{
			write(1, "-", 1);
			n = n * -1;
		}
		if (n >= 0 && n <= base_len(base) - 1)
			write(1, &base[n], 1);
		if (n > base_len(base) - 1)
		{
			ft_putnbr_base(n / base_len(base), base);
			ft_putnbr_base(n % base_len(base), base);
		}
	}
	return ;
}
