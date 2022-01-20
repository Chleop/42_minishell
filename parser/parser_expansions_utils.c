/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expansions_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:51:50 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/20 19:22:47 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	remove_quotes(char **token)
{
	int		i;
	char	c;
	char	*temp;

	i = 0;
	c = '\0';
	temp = NULL;
	while ((*token)[i])
	{
		if (((*token)[i] == '\'') || ((*token)[i] == '\"'))
		{
			if (is_paired((*token)[i], *token, i + 1))
			{
				c = (*token)[i];
				temp = *token;
				*token = ft_calloc(ft_strlen(temp) - 1, sizeof(char));
				if (!*token)
					return (ft_error("Error: malloc failed"));
				i = 0;
				while (temp[i] && (temp[i] != c))
				{
					(*token)[i] = temp[i];
					i++;
				}
				i++;
				while (temp[i] && (temp[i] != c))
				{
					(*token)[i - 1] = temp[i];
					i++;
				}
				if (!temp[i])
				{
					free (temp);
					return (1);
				}
				i++;
				while ((i - 2) >= 0 && (temp[i]))
				{
					(*token)[i - 2] = temp[i];
					i++;
				}
				i = -1;
				free (temp);
				temp = NULL;
			}
		}
		i++;
	}
	return (1);
}


