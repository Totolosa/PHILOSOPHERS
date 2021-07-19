/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 16:56:03 by tdayde            #+#    #+#             */
/*   Updated: 2020/11/25 16:21:25 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	int				i;
	unsigned char	*tdest;
	unsigned char	*tsrc;

	i = -1;
	tdest = (unsigned char *)dest;
	tsrc = (unsigned char *)src;
	if (!dest && !src)
		return (dest);
	if (tdest > tsrc)
	{
		i = (int)len - 1;
		while (i >= 0)
		{
			tdest[i] = tsrc[i];
			i--;
		}
	}
	else
	{
		while (++i < (int)len)
			tdest[i] = tsrc[i];
	}
	return ((void *)tdest);
}
