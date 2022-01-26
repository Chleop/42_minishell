/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dollar_expansions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 13:34:16 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/24 15:59:13 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_to_params(t_data *data, int i, char *param)
{
	char	**temp;
	int		l;

	printf("param = %s\n", param);
	data->cmd[i].nr_param++;
	temp = data->cmd[i].param;
	data->cmd[i].param = (char **)ft_calloc(data->cmd[i].nr_param + 1, sizeof(char *));
	if (!data->cmd[i].param)
		return (0);
	if (temp)
	{
		l = 0;
		while (temp[l])
		{
			data->cmd[i].param[l] = ft_strdup(temp[l]);
			free (temp[l]);
			l++;
		}
		free(temp);
		if (!data->cmd[i].param[l])
			return (0);
	}
	data->cmd[i].param[data->cmd[i].nr_param - 1] = ft_strdup(param);
	if (!data->cmd[i].param[data->cmd[i].nr_param - 1])
		return (0);
	data->cmd[i].param[data->cmd[i].nr_param] = NULL;
	printf("premier param = %s\n", data->cmd[i].param[data->cmd[i].nr_param - 1]);
	return (1);
}

int	tidy_commands(t_data *data, char **token)
{
	int		i;
	int		j;
	char	*param;

	i = 0;
	j = 0;
	param = NULL;
			
	while ((*token)[i])
	{
		if ((((*token)[i] == ' ') || (*token)[i] == '\0'))
		{
			param = ft_substr(*token, j, i);
			printf("param = %s\n", param);
			if (!param)
				return (0);
			add_to_params(data, i, param);
			free (param);
			if ((*token)[i] == '\0')
				return (1);
			j = i + 1;
		}
		i++;
	}
	return (1);
}

int	tidy_token(t_data *data, char **token, int cmd_nr, int tok_nr)
{
	char	*temp;

	if (data->cmd[cmd_nr].qualif[tok_nr] == CMD)
	{
		// exit(1);
		temp = *token;
		*token = find_path(data->envp, *token);
		free (temp);
		if (!tidy_commands(data, token))
			return (0);
		printf ("commande = %s\n", data->cmd[cmd_nr].param[0]);
		data->cmd[cmd_nr].qualif[tok_nr] = EMPTY;
	}
	return (1);
}

int	is_quoted(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (((token[i] == '\'') || (token[i] == '\"')) && is_paired(token[i], token, i + 1))
			return (token[i]);
		i++;
	}
	return (0);
}

int	expand_one_dollar(t_data *data, char **token, int cmd_nr, int tok_nr)
{
	int	firstq_i;
	int	secondq_i;
	int	quote;

	quote = is_quoted(*token);
	if (quote)
	{
		firstq_i = ft_strchr(*token, quote) - *token;
		secondq_i = ft_strchr(*token + firstq_i + 1, quote) - *token;
		if (!remove_quotes(token, firstq_i, secondq_i))
			return (0);
	}
	if (quote != '\'')
		manage_expansions(data, token);
	if (!tidy_token(data, token, cmd_nr, tok_nr))
		return (0);
	return (1);
}

int	expand_and_classify_dollars(t_data *data)
{
	int i;
	int	j;

	i = 0;
	while (i < data->nr_cmds)
	{
		j = 0;
		while (j < data->cmd[i].nr_tok)
		{
			if (ft_strchr(data->cmd[i].tok[j], '$'))
				expand_one_dollar(data, &(data->cmd[i].tok[j]), i, j);
			j++;
		}
		i++;
	}
	return (1);
}
