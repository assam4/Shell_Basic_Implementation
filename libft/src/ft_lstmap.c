/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:48:59 by saslanya          #+#    #+#             */
/*   Updated: 2025/02/11 21:50:13 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*core;
	t_list	*new_node;
	void	*cont;

	if (!lst || !f || !del)
		return (NULL);
	core = NULL;
	while (lst)
	{
		cont = f(lst->content);
		new_node = ft_lstnew(cont);
		if (!new_node)
		{
			free(cont);
			ft_lstclear(&core, del);
			return (NULL);
		}
		if (!core)
			core = new_node;
		else
			(ft_lstlast(core))->next = new_node;
		lst = lst->next;
	}
	return (core);
}
