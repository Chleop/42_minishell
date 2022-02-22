/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BI_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 14:07:45 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/22 12:36:01 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_from_envp(t_envp *envp, char *name)
{
	while (envp)
	{
		if (!ft_strncmp(envp->name, name, ft_strlen(envp->name) + 1))
		{
			envp->previous->next = envp->next;
			if (envp->next)
				envp->next->previous = envp->previous;
			free_node_envp(envp);
			return ;
		}
		envp = envp->next;
	}
}

int	ft_unset(t_cmd *cmd)
{
	int		i;
	int		status;
	t_envp	*temp;

	temp = cmd->data->envp;
	status = 0;
	i = 0;
	while (cmd->param[++i])
	{
		if (check_identifier(cmd->param[i], UNSET))
			remove_from_envp(cmd->data->envp, cmd->param[i]);
		else
			status++;
	}
	if (status)
		return (0);
	else
		return (1);
}
