/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 16:36:55 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/31 17:48:42 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_char_table(char *str, char **tab)
{
	int	i;

	if (!tab)
	{
		printf("tab [%s] n'existe pas\n", str);
		return ;
	}
	i = 0;
	while (tab[i])
	{
		printf("%s[%d] = [%s]\n", str, i, tab[i]);
		i++;
	}
	return ;
}

void	print_int_table(int *tab)
{
	int	i;

	if (!tab)
	{
		printf("Int Stab n'existe pas\n");
		return ;
	}
	i = 0;
	while (tab[i])
	{
		printf("Int tab %d = %d\n", i, tab[i]);
		i++;
	}
	return ;
}

void	print_cmds_and_tokens(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nr_cmds)
	{
		printf("Commande %d\n", i);
		print_char_table("Token", data->cmd[i].tok);
		print_int_table(data->cmd[i].qualif);
		i++;
	}
}

void	print_cmd_parameters(t_data *data)
{
	int	i;

	printf("LES PARAMETRES SONT:\n");
	i = 0;
	while (i < data->nr_cmds)
	{
		printf ("Commande %d\n", i);
		printf("Nb param = %d\n", data->cmd[i].nr_param);
		print_char_table("Param", data->cmd[i].param);
		printf("Nb in files = %d\n", data->cmd[i].nr_in);
		print_char_table("IN file", data->cmd[i].i);
		printf("Nb out files = %d\n", data->cmd[i].nr_out);
		print_char_table("OUT file", data->cmd[i].o);
		print_int_table(data->cmd[i].type);
		i++;
	}
}
