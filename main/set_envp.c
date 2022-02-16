/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:09:29 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/09 14:55:54 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_shlvl(t_envp **envp, char *shlvl)
{
	char	*itoa;

	itoa = ft_itoa(ft_atoi(shlvl) + 1);
	free_string(&shlvl);
	shlvl = ft_strjoin("SHLVL=", itoa);
	free_string(&itoa);
	add_to_envp(*envp, shlvl);
	free_string(&shlvl);
	remove_from_envp(*envp, "OLDPWD");
	add_to_envp(*envp, "OLDPWD");
	remove_from_envp(*envp, "_");
}

void	adapt_values(t_envp **envp)
{
	t_envp	*temp;
	char	*shlvl;

	shlvl = NULL;
	temp = *envp;
	while (temp)
	{
		if (!ft_strncmp("SHLVL\0", temp->name, 6))
		{
			shlvl = ft_strdup(temp->var);
			break ;
		}
		temp = temp->next;
	}
	if (shlvl)
		update_shlvl(envp, shlvl);
}

int	init_empty_env(t_envp **envp)
{
	t_envp	*new;
	char	*pwd;
	char	*temp;

	temp = getcwd(NULL, 0);
	pwd = ft_strjoin("PWD=", temp);
	free_string(&temp);
	new = new_item(pwd);
	if (new == 0)
		return (0);
	add_item_back(envp, new);
	free_string(&pwd);
	new = new_item("SHLVL=2\0");
	if (new == 0)
		return (0);
	add_item_back(envp, new);
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
