/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:01:11 by cproesch          #+#    #+#             */
/*   Updated: 2021/06/16 11:01:14 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next_element;

	if ((!lst) || (!(*lst)) || (!del))
		return ;
	while (*lst)
	{
		next_element = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = next_element;
	}
}
