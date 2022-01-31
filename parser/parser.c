/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:55:08 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/31 17:05:44 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	review_operators(char **token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if ((token[i][0] == '|') || (token[i][0] == '>')
		|| (token[i][0] == '<'))
		{
			if (ft_strncmp(token[i], "|\0", 2) && ft_strncmp(token[i], "<\0", 2)
				&& ft_strncmp(token[i], ">\0", 2)
				&& ft_strncmp(token[i], ">>\0", 3)
				&& ft_strncmp(token[i], "<<\0", 3)
				&& ft_strncmp(token[i], ">|\0", 3))
				return (ft_error("Syntax error"));
			else if (!token[i + 1])
				return (ft_error("Syntax error"));
			else if (((i - 1) > -1) && ((token[i - 1][0] == '>') || (token[i - 1][0] == '<')))
				return (ft_error("Syntax error"));
		}
		i++;
	}
	return (1);
}

int	parse(t_data *data, char **token)
{
	if (!initialize_data(data, token))
		return (0);
	if (!review_operators(token))
		return (0);
	if (!initialize_cmds(data, token))
		return (0);
	if (!grammatize_tokens(data))
		return (0);
	if (!set_into_structure(data))
		return (0);
	print_cmd_parameters(data);
	return (1);
}
