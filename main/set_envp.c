/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:09:29 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/01 17:42:09 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envp(t_cmd *cmd)
{
	int		i;
	t_envp	*temp;

	i = -1;
	while (cmd->param[++i])
	{
		if (cmd->param[i])
		{
			free(cmd->param[i]);
			cmd->param[i] = NULL;
		}
	}
	while (cmd->data->envp)
	{
		temp = cmd->data->envp;
		cmd->data->envp = cmd->data->envp->next;
		if (temp->name != NULL)
		{
			free(temp->name);
			temp->name = NULL;
		}
		if (temp->var != NULL)
		{		
			free(temp->var);
			temp->var = NULL;
		}
		free(temp);
		temp = NULL;
	}
}

void	adapt_values(t_envp **envp)
{
	t_envp	*temp;
	char	*shlvl;
	int		new;

	shlvl = NULL;
	temp = *envp;
	while (temp)
	{
		if (!ft_strncmp("SHLVL\0", temp->name, 6))
		{
			printf("Old is: %s\n", temp->var);
			shlvl = ft_strdup(temp->var);
			break ;
		}
		temp = temp->next;
	}
	new = ft_atoi(shlvl) + 1;
	free(shlvl);
	shlvl = NULL;
	shlvl = ft_strjoin("SHLVL=", ft_itoa(new));
	add_to_envp(*envp, shlvl);
	remove_from_envp(*envp, "OLDPWD");
	add_to_envp(*envp, "OLDPWD");
	remove_from_envp(*envp, "_");
	free(shlvl);
	shlvl = NULL;
}

int	init_empty_env(t_envp **envp)
{
	t_envp	*new;
	char	*pwd;

	pwd = ft_strjoin("PWD=", getcwd(NULL, 0));
	new = new_item(pwd);
	if (new == 0)
		return (0);
	add_item_back(envp, new);
	new = new_item("SHLVL=2\0");
	if (new == 0)
		return (0);
	add_item_back(envp, new);
	free(pwd);
	pwd = NULL;
	return (1);
}

int	init_envp(t_data *data, char *envp[])
{
	int		i;
	int		j;
	t_envp	*new;

	i = 0;
	while (envp[i])
		i++;
	if (i)
	{
		j = -1;
		while (++j < i)
		{
			new = new_item(envp[j]);
			if (new == 0)
				return (-1);
			add_item_back(&data->envp, new);
		}
		adapt_values(&data->envp);
	}
	else
	{
		if (init_empty_env(&data->envp) == 0)
			return (-1);
	}
	return (1);
}
