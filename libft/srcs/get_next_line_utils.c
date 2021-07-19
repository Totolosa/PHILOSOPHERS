/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 15:17:12 by tdayde            #+#    #+#             */
/*   Updated: 2021/03/12 12:31:11 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*dest;

	i = -1;
	j = -1;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	dest = malloc(sizeof(char) * (gnl_strlen(s1) + gnl_strlen(s2) + 1));
	if (dest == NULL)
		return (NULL);
	while (s1[++i])
		dest[i] = s1[i];
	while (s2[++j])
		dest[i + j] = s2[j];
	dest[i + j] = '\0';
	free(s1);
	s1 = NULL;
	return (dest);
}

char	*gnl_strdup(const char *s)
{
	char	*dest;
	int		i;

	dest = malloc(sizeof(char) * gnl_strlen(s) + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*content_after_linebreak(char *s, char c)
{
	int		i;
	int		j;
	char	*new;

	new = NULL;
	i = 0;
	while (s[i] != c)
		i++;
	i++;
	j = 0;
	while (s[i + j])
		j++;
	new = malloc(sizeof(char) * (j + 1));
	if (!new)
		return (NULL);
	j = 0;
	while (s[i])
		new[j++] = s[i++];
	new[j] = '\0';
	free(s);
	s = NULL;
	return (new);
}

char	*content_before_linebreak(char *buff, char c)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	while (buff[i] != c)
		i++;
	new = malloc(sizeof(char) * (i + 1));
	if (!new)
		return (NULL);
	j = -1;
	while (++j < i)
		new[j] = buff[j];
	new[j] = '\0';
	return (new);
}
