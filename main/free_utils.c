/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:23:36 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/03 13:08:09 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_del_stringtab(char ***tab)
{
	int	i;

	i = 0;
	if (!*tab)
		return ;
	while ((*tab)[i])
	{
		if ((*tab)[i])
		{
			free((*tab)[i]);
			(*tab)[i] = NULL;
		}
		i++;
	}
	free(*tab);
	*tab = NULL;
}

void	ft_free_parser(t_data *data, char ***token)
{
	int	i;

	i = 0;
	if (*token)
		ft_del_stringtab(token);
	if (data->cmd)
	{
		while (i < data->nr_cmds)
		{
			if (data->cmd[i].tok)
				ft_del_stringtab(&(data->cmd[i].tok));
			if (data->cmd[i].qualif)
				free(data->cmd[i].qualif);
			i++;
		}
	}
}

void	ft_free_data(t_data *data, int code)
{
	int	i;

	i = 0;
	if (code)
		free_envp(data);
	if (data->cmd)
	{
		while (i < data->nr_cmds)
		{
			if (data->cmd[i].param)
				ft_del_stringtab(&(data->cmd[i].param));
			i++;
		}
		free (data->cmd);
		data->cmd = NULL;
	}
}

int	ft_error(char *str)
{
	printf("%s\n", str);
	return (0);
}

void	final_exit(t_data *data, int i, char *str)
{
	free_envp(data);
	printf("%s\n", str);
	exit (i);
}
