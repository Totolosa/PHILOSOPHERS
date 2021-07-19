/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:59:03 by tdayde            #+#    #+#             */
/*   Updated: 2021/04/12 23:54:39 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

int		get_next_line(int fd, char **line);

size_t	gnl_strlen(const char *s);

char	*gnl_strjoin(char *s1, char *s2);

char	*gnl_strdup(const char *s);

char	*content_after_linebreak(char *s, char c);

char	*content_before_linebreak(char *buff, char c);

#endif
