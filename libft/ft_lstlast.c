/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 18:01:14 by cproesch          #+#    #+#             */
/*   Updated: 2021/09/21 14:56:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*next_element;

	if (!lst)
		return (0);
	if (!lst->next)
		return (lst);
	next_element = lst->next;
	while (next_element->next)
		next_element = next_element->next;
	return (next_element);
}
