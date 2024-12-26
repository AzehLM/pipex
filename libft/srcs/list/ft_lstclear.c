/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:16:38 by gueberso          #+#    #+#             */
/*   Updated: 2024/11/11 18:18:34 by gueberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*new_list;
	t_list	*tmp;

	if (lst)
	{
		new_list = *lst;
		while (new_list)
		{
			tmp = new_list;
			new_list = new_list->next;
			ft_lstdelone(tmp, del);
		}
		*lst = NULL;
	}
}
