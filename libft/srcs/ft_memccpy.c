/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 16:56:03 by tdayde            #+#    #+#             */
/*   Updated: 2020/11/23 16:57:01 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*tmpd;
	unsigned char	*tmps;

	i = -1;
	tmpd = (unsigned char *)dest;
	tmps = (unsigned char *)src;
	while (++i < n)
	{
		tmpd[i] = tmps[i];
		if (tmps[i] == (unsigned char)c)
		{
			return ((void *)&tmpd[i + 1]);
		}
	}
	return (NULL);
}
