/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 14:59:57 by tdayde            #+#    #+#             */
/*   Updated: 2021/03/10 14:52:28 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nb_of_digit(long int n)
{
	int	nb_of_char;

	nb_of_char = 0;
	if (n < 0)
	{
		nb_of_char++;
		n *= -1;
	}
	while (n / 10 > 0)
	{
		nb_of_char++;
		n /= 10;
	}
	return (nb_of_char + 1);
}

char	*ft_itoa(int n)
{
	int			i;
	int			nb_of_char;
	long int	nb;
	char		*res;

	nb = (long int)n;
	nb_of_char = nb_of_digit(nb);
	res = malloc(sizeof(char) * (nb_of_char + 1));
	if (res == NULL)
		return (NULL);
	if (nb == 0)
		res[0] = '0';
	if (nb < 0)
	{
		res[0] = '-';
		nb *= -1;
	}
	i = nb_of_char;
	res[i--] = '\0';
	while (nb > 0)
	{
		res[i--] = nb % 10 + '0';
		nb /= 10;
	}
	return (res);
}
