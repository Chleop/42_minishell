/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BI_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:14:38 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/22 12:34:46 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_first_char(char *id, int code)
{
	if (ft_isdigit(id[0]) || id[0] == '=' || id[0] == '\0')
	{
		if (code == 3)
			return (ft_error2("export: not a valid identifier", id, 1));
		else if (code == 4)
			return (ft_error2("unset: not a valid identifier", id, 1));
		else
			return (0);
	}
	return (1);
}

int	check_identifier(char *id, int code)
{
	int	i;

	if (!check_first_char(id, code))
		return (0);
	i = -1;
	while (id[++i] != '=' && id[i] != '\0')
	{
		if (!(ft_isalnum(id[i]) || (id[i] == '_')))
		{
			if (code == 3)
				return (ft_error2("export: not a valid identifier", id, 1));
			else if (code == 4)
				return (ft_error2("unset: not a valid identifier", id, 1));
			else
				return (0);
		}
	}
	if (id[i] == '=' && code == 4)
		return (ft_error2("unset: not a valid identifier", id, 1));
	return (1);
}

void	add_to_envp(t_envp *envp, char *var)
{
	t_envp	*new;
	t_envp	*temp;

	temp = envp;
	new = new_item(var);
	while (envp)
	{
		if (ft_strncmp(envp->name, new->name, ft_strlen(envp->name) + 1) == 0)
		{
			if (new->var)
			{
				new->next = envp->next;
				new->previous = envp->previous;
				envp->previous->next = new;
				if (envp->next)
					envp->next->previous = new;
				free_node_envp(envp);
			}
			else
				free_node_envp(new);
			return ;
		}	
		envp = envp->next;
	}
	add_item_back(&temp, new);
}

int	ft_export_prefork(t_cmd *cmd)
{
	int		i;
	int		status;

	i = 0;
	status = 0;
	while (cmd->param[++i])
	{
		if (check_identifier(cmd->param[i], EXPORT))
			add_to_envp(cmd->data->envp, cmd->param[i]);
		else
			status++;
	}
	if (status)
		return (0);
	else
		return (1);
}
