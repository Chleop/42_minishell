/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes_removal.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:51:50 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/24 13:44:38 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cpy_before_quotes(char **token, char *temp, int firstq_i)
{
	int		start;
	int		end;

	start = 0;
	end = firstq_i;
	ft_memcpy(*token + start, temp + start, end - start);
	return ;
}

void	cpy_between_quotes(char **token, char *temp, int firstq_i, int secondq_i)
{
	int		start;
	int		end;

	start = firstq_i;
	end = secondq_i;
	ft_memcpy(*token + start, temp + start + 1, end - start - 1);
	return ;
}

void	cpy_after_quotes(char **token, char *temp, int secondq_i)
{
	int		start;
	int		end;

	start = secondq_i;
	end = ft_strlen(temp);
	ft_memcpy(*token + start - 1, temp + start + 1, end - start - 1);
	return ;
}

int	remove_quotes(char **token, int firstq_i, int secondq_i)
{
	char	*temp;

	temp = NULL;
	temp = *token;
	*token = ft_calloc(ft_strlen(temp) - 1, sizeof(char));
	if (!*token)
		return (ft_error("Error: malloc failed"));
	cpy_before_quotes(token, temp, firstq_i);
	cpy_between_quotes(token, temp, firstq_i, secondq_i);
	if (temp[secondq_i + 1])
		cpy_after_quotes(token, temp, secondq_i);
	free (temp);
	temp = NULL;
	return (1);
}

int	identify_remove_quotes(char **token)
{
	int	i;
	int	firstq_i;
	int	secondq_i;

	i = 0;
	while ((*token)[i])
	{
		if (((*token)[i] == '\'') || ((*token)[i] == '\"'))
		{
			firstq_i = i;
			secondq_i = is_paired((*token)[i], *token, i + 1);
			if (secondq_i)
				remove_quotes(token, firstq_i, secondq_i);
		}
		i++;
	}
	return (1);
}
