/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:55:08 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/17 19:29:40 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	initialize_data(t_data *data, char **token)
{
	data->nr_token = count_token(token);
	data->nr_cmds = count_pipes(data, token) + 1;
	printf("nb de cmds = %d\n", data->nr_cmds);
	data->cmd = (t_cmd *)ft_calloc(data->nr_cmds, sizeof(t_cmd));
	if (!data->cmd)
		return (ft_error("Error:malloc failed\n"));
	return (1);
}

void	initialize_grammar(int **grammar, int nr_token)
{
	int	i;

	i = 0;
	while (i < nr_token)
	{
		(*grammar)[i] = EMPTY;
		i++;
	}
	return ;
}

int	divide_token(t_data *data, char **token)
{
	int	i;
	// int	j;

	i = 0;
	// j = 0;
	while (i < data->nr_cmds)
	{
		while (!ft_strchr(token[i], '|'))
		{
			// data->cmd[i].tok[j] = (char *)ft_calloc(ft_strlen(token[i]) + 1, sizeof(char));
			// exit(1);
			// j++;
			i++;
		}
		i++;
	}
	return (1);
}

int	initialize_cmds(t_data *data, char **token)
{
	int	pipe_index[1024];
	int	i;
	int	j;
	int	k;
	int l;

	i = 0;
	j = 0;
	l = 0;
	while (j < data->nr_cmds)
	{
		k = i;
		while ((i < data->nr_token) && (!ft_strchr(token[i], '|')))
			i++;
		if ((i == (data->nr_token - 1)) && (ft_strchr(token[i], '|')))
			return (ft_error("Syntax error"));
		pipe_index[j] = i;
		printf ("pipe index %d = %d\n", j, i);
		data->cmd->tok = (char **)ft_calloc((pipe_index[j] - k) + 1, sizeof(char *));
		if (!data->cmd->tok)
			return (ft_error("Error:malloc failed\n"));
		l = 0;
		printf ("k = %d, pipe_index[j] = %d\n", k, pipe_index[j]);
		while (k < pipe_index[j])
		{
			printf("token a copier = %s\n", token[k]);
			printf("j = %d, l = %d, k = %d\n", j, l, k);
			data->cmd[j].tok[l] = (char *)ft_calloc(ft_strlen(token[k]) + 1, sizeof(char));
			printf ("Apres le malloc\n");
			if (!ft_memcpy(data->cmd[j].tok[l], token[k], ft_strlen(token[k])))
				return (0);
				printf ("Apres le memcpy\n");
			l++;
			k++;
		}
		print_char_table(data->cmd[j].tok);
		if (i == data->nr_token)
			break;
		i++;
		j++;
	}
	exit(1);
	return (1);
}

int	parse(t_data *data, char **token)
{
	int	*grammar;
	int	i;

	if (!initialize_data(data, token))
		return (0);
	if (!initialize_cmds(data, token))
		return (0);
	if (!divide_token(data, token))
		return (0);
	ft_del_stringtab(&token);
	grammar = (int *)ft_calloc(data->nr_token + 1, sizeof(int));
	if (!grammar)
		return (ft_error("Error:malloc failed\n"));
	initialize_grammar(&grammar, data->nr_token);
	i = 0;
	while (token[i])
	{
		if (ft_strchr(token[i], '$'))
			grammar[i] = VAR;
		else if ((i > 0) && (ft_strchr(token[i - 1], '<')))
			grammar[i] = RED_IN;
		else if ((i > 0) && (ft_strchr(token[i - 1], '>')))
			grammar[i] = RED_OUT_S;
		// else if ((i > 0) && (ft_strchr(token[i - 1], '>>')))
		// 	grammar[i] = RED_OUT_D;
		// else if ((i > 0) && (ft_strchr(token[i - 1], '<<')))
		// 	grammar[i] = HERE_END;

// A REVOIR CAR LES OPERATEURS NE SONT PAS ENCORE NETTOYES !!!
		i++;
	}
	
	
	print_int_table(grammar);
	return (1);
}