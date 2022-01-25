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




// int	add_to_params(t_data *data, int i, char *param)
// {
// 	char	**temp;
// 	int		l;

// 	printf("param = %s\n", param);
// 	data->cmd[i].nr_param++;
// 	temp = data->cmd[i].param;
// 	data->cmd[i].param = (char **)ft_calloc(data->cmd[i].nr_param + 1, sizeof(char *));
// 	if (!data->cmd[i].param)
// 		return (0);
// 	if (temp)
// 	{
// 		l = 0;
// 		while (temp[l])
// 		{
// 			data->cmd[i].param[l] = ft_strdup(temp[l]);
// 			free (temp[l]);
// 			l++;
// 		}
// 		free(temp);
// 		if (!data->cmd[i].param[l])
// 			return (0);
// 	}
// 	data->cmd[i].param[data->cmd[i].nr_param - 1] = ft_strdup(param);
// 	if (!data->cmd[i].param[data->cmd[i].nr_param - 1])
// 		return (0);
// 	data->cmd[i].param[data->cmd[i].nr_param] = NULL;
// 	printf("premier param = %s\n", data->cmd[i].param[data->cmd[i].nr_param - 1]);
// 	return (1);
// }

// int	tidy_commands(t_data *data, char **token)
// {
// 	int		i;
// 	int		j;
// 	int		c;
// 	char	*param;

// 	i = 0;
// 	j = 0;
// 	while ((*token)[i])
// 	{
// 		if ((((*token)[i] == '\'') || ((*token)[i] == '\"'))
// 		&& is_paired((*token)[i], *token, i + 1))
// 		{
// 			c = (*token)[i];
// 			i++;
// 			while ((*token)[i] != c)
// 				i++;
// 		}
// 		else if ((((*token)[i] == ' ') || (*token)[i] == '\0'))
// 		{
// 			param = ft_substr(*token, j, i);
// 			printf("param = %s\n", param);
// 			if (!param)
// 				return (0);
// 			add_to_params(data, i, param);
// 			free (param);
// 			if ((*token)[i] == '\0')
// 				return (1);
// 			j = i + 1;
// 		}
// 		i++;
// 	}
// 	return (1);
// }

// int	tidy_token(t_data *data, char **token, int cmd_nr, int tok_nr)
// {
// 	if (data->cmd[cmd_nr].qualif[tok_nr] == CMD)
// 	{
// 		if (!tidy_commands(data, token))
// 			return (0);
// 		data->cmd[cmd_nr].qualif[tok_nr] = EMPTY;
// 	}
// 	return (1);
// }

// int	expand_one_dollar(t_data *data, char **token, int cmd_nr, int tok_nr)
// {
// 	int	i;
// 	int	firstq_i;
// 	int	secondq_i;

// 	i = 0;
// 	while ((*token)[i])
// 	{
// 		if ((*token)[i] == '\'')
// 		{
// 			firstq_i = i;
// 			secondq_i = is_paired((*token)[i], *token, i + 1);
// 	printf ("token = %s\n", *token);
// 			if (secondq_i)
// 			{
// 				if (!remove_quotes(token, firstq_i, secondq_i, &i)
// 				|| !tidy_token(data, token, cmd_nr, tok_nr))
// 					return (0);
// 			}
// 			else
// 			{
// 				// if (!expand_variable((*token)[i])
// 				// || !tidy_token(data, &((*token)[i])))
// 				if (!tidy_token(data, token, cmd_nr, tok_nr))
// 					return (0);
// 			}
// 		}
// 		else if ((*token)[i] == '\"')
// 		{
// 			firstq_i = i;
// 			secondq_i = is_paired((*token)[i], *token, i + 1);
// 			if (secondq_i)
// 			{
// 				if (!remove_quotes(token, firstq_i, secondq_i, &i))
// 					return (0);
// 			}
// 				// if (!expand_variable((*token)[i])
// 				// || !tidy_token(data, &((*token)[i])))
// 				if (!tidy_token(data, token, cmd_nr, tok_nr))
// 					return (0);
// 		}
// 		else
// 		{
// 				// if (!expand_variable((*token)[i])
// 				// || !tidy_token(data, &((*token)[i])))
// 				if (!tidy_token(data, token, cmd_nr, tok_nr))
// 					return (0);
// 				printf("ici ca passe\n");
// 		}
// 		i++;
// 	}
// 	return (1);
// }

int	is_quoted(int qtype, char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if ((token[i] == qtype) && is_paired(qtype, token, i + 1))
			return (1);
		i++;
	}
	return (0);
}

int	expand_one_dollar(t_data *data, char **token, int cmd_nr, int tok_nr)
{
	if (is_quoted('\'', *token))
	{
		if (!remove_quotes(*token, ft_strchr(*token, '\''), ft_strchr(*token + 1, '\''), &i)
			|| !tidy_token(data, token, cmd_nr, tok_nr))
					return (0);
	}
	else if (is_quoted('\"', *token))
	{
		
	}
	else
	{
		
	}
	i++;
	
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
