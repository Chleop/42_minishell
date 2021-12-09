/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_exit_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 11:24:59 by cproesch          #+#    #+#             */
/*   Updated: 2021/12/09 12:30:31 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_del_stringtab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	ft_exit(t_data **data, int exit_code)
{
	int	i;

	i = 0;
	if ((data != NULL) && ((*data) != NULL))
	{
		while (i < (*data)->max_cmd)
		{
			if ((*data)->cmd[i] && (*data)->cmd[i][0])
				ft_del_stringtab((*data)->cmd[i]);
			if ((*data)->cmd_path[i] && (*data)->cmd_path[i][0])
				free((*data)->cmd_path[i]);
			i++;
		}
		free (*data);
	}
	exit (exit_code);
}

void	error_message(char *error_message, t_data **data)
{
	perror(error_message);
	ft_exit(data, 2);
}
