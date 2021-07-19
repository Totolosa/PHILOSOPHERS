/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 17:15:25 by tdayde            #+#    #+#             */
/*   Updated: 2021/03/10 14:53:22 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*new;
	t_list	*cell;

	tmp = lst;
	new = NULL;
	while (tmp != NULL)
	{
		cell = ft_lstnew(tmp->content);
		if (cell == NULL)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		cell->content = f(cell->content);
		ft_lstadd_back(&new, cell);
		tmp = tmp->next;
	}
	return (new);
}
