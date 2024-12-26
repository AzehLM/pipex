/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:38:42 by gueberso          #+#    #+#             */
/*   Updated: 2024/11/11 23:38:42 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*first_node;
	void	*tmp;

	first_node = NULL;
	while (lst)
	{
		tmp = f(lst->content);
		new_list = ft_lstnew(tmp);
		if (!new_list)
		{
			del(tmp);
			ft_lstclear(&first_node, del);
			return (NULL);
		}
		ft_lstadd_back(&first_node, new_list);
		lst = lst->next;
	}
	return (first_node);
}
