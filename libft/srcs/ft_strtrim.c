/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 20:15:31 by tdayde            #+#    #+#             */
/*   Updated: 2021/03/10 15:03:43 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_on_set(char c, const char *set)
{
	int	i;

	i = -1;
	while (set[++i])
		if (set[i] == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		len_dest;
	char	*dest;

	i = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	while (is_on_set(s1[i], set))
		i++;
	if (s1[i] == '\0')
		return (ft_calloc(1, 1));
	j = ft_strlen(s1) - 1;
	while (is_on_set(s1[j], set))
		j--;
	len_dest = j - i + 2;
	dest = malloc(sizeof(char) * len_dest);
	if (dest == NULL)
		return (NULL);
	j = -1;
	while (++j < len_dest - 1)
		dest[j] = s1[i + j];
	dest[j] = '\0';
	return (dest);
}
