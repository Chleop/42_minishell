/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:21:43 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/07 10:14:16 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**convert_envp(t_envp *envp)
{
	t_envp	*e_temp;
	char	**table;
	char	*s_temp;
	char	*s_temp2;
	int		size;
	int		i;

	e_temp = envp;
	size = size_list(envp);
	table = ft_calloc(size + 1, sizeof(char *));
	i = -1;
	while (++i < size)
	{
		s_temp = ft_strjoin(e_temp->name, "=");
		s_temp2 = ft_strjoin(s_temp, e_temp->var);
		free_string(s_temp);
		table[i] = s_temp2;
		e_temp = e_temp->next;
	}
	return (table);
}

int	size_list(t_envp *head)
{
	t_envp	*temp;
	int		i;

	temp = head;
	i = 0;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

t_envp	*last_list_item(t_envp *head)
{
	if (head)
		while (head->next)
			head = head->next;
	return (head);
}

void	add_item_back(t_envp **list, t_envp *new)
{
	t_envp	*last;

	if (*list == 0)
		*list = new;
	else
	{
		last = last_list_item(*list);
		new->previous = last;
		last->next = new;
	}
}

t_envp	*new_item(char *string)
{
	t_envp	*node;
	int		i;
	int		j;

	node = malloc(sizeof(t_envp));
	if (!node)
		return (0);
	i = 0;
	while (!(string[i] == '=' || string[i] == '\0'))
		i++;
	node->name = ft_substr(string, 0, i);
	if (string[i] == '=')
	{
		i++;
		j = i;
		while (string[j])
			j++;
		node->var = ft_substr(string, i, j - i);
	}
	else
		node->var = NULL;
	node->printed = 0;
	node->next = NULL;
	node->previous = NULL;
	return (node);
}
