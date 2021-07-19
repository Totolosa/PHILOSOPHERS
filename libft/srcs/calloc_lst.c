/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 13:56:59 by tdayde            #+#    #+#             */
/*   Updated: 2021/04/26 17:51:35 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*quit_prog(t_list **lst)
{
	ft_lstclear(lst, free);
	write(1, "Error malloc\n", 13);
	exit (1);
}

void	*calloc_lst(unsigned long size, t_list **lst)
{
	t_list	*new;
	void	*alloc;

	alloc = malloc(size);
	if (alloc == NULL)
		return (quit_prog(lst));
	ft_bzero(alloc, size);
	new = malloc(sizeof(t_list));
	if (new == NULL)
	{
		free(alloc);
		return (quit_prog(lst));
	}
	else
	{
		new->next = NULL;
		new->content = alloc;
		ft_lstadd_back(lst, new);
		return (alloc);
	}
}
