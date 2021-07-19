/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 16:57:10 by tdayde            #+#    #+#             */
/*   Updated: 2021/03/11 12:15:16 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*free_mem(char **tab, int k)
{
	while (k >= 0)
		free(tab[k--]);
	free(tab);
	return (NULL);
}

static char	*malloc_word(char ***tab, int len_word, int *j)
{
	(*tab)[*j] = malloc(sizeof(char) * (len_word + 1));
	if ((*tab)[*j] == NULL)
		return (free_mem(*tab, *j - 1));
	return ((*tab)[*j]);
}

static char	**malloc_tab(char *str, char c)
{
	int		i;
	int		j;
	int		len_word;
	char	**tab;

	i = 0;
	j = 0;
	tab = malloc(sizeof(char *) * ft_count_words(str, c) + 1);
	if (!tab)
		return (NULL);
	while (str[i])
	{
		len_word = 0;
		while (str[i] == c && str[i])
			i++;
		while (str[i] != c && str[i])
		{
			len_word++;
			i++;
		}
		if (len_word > 0)
			tab[j++] = malloc_word(&tab, len_word, &j);
	}
	tab[j] = NULL;
	return (tab);
}

static char	**fill_tab(char **tab, char *str, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (str[i] && j < ft_count_words(str, c))
	{
		k = 0;
		while (str[i] == c && str[i])
			i++;
		while (str[i] != c && str[i])
			tab[j][k++] = str[i++];
		tab[j][k] = '\0';
		if (str[i] == c)
			j++;
	}
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	*str;
	char	**tab;

	if (s == NULL)
		return (NULL);
	str = (char *)s;
	tab = malloc_tab(str, c);
	if (!tab)
		return (NULL);
	tab = fill_tab(tab, str, c);
	return (tab);
}
