/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:37:25 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/08 15:42:24 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exit_code_expansion(t_data *data, char *to_be_exp)
{
	char	*exp;
	char	*exit_char;
	char	*post;

	exit_char = ft_itoa(data->exit_code);
	post = ft_strdup(to_be_exp + 1);
	exp = ft_strjoin(exit_char, post);
	free(exit_char);
	free(post);
	return (exp);
}

char	*get_expansion(t_data *data, char *to_be_exp)
{
	char	*exp;
	t_envp	*temp;

	temp = data->envp;
	exp = NULL;
	if (to_be_exp[0] == '?')
		return (exit_code_expansion(data, to_be_exp));
	while (temp && ft_strlen(to_be_exp))
	{
		if (!ft_strncmp(temp->name, to_be_exp, ft_strlen(temp->name) + 1))
		{
			exp = ft_strdup(temp->var);
			break ;
		}
		temp = temp->next;
	}
	if (!exp)
		exp = ft_strdup("\0");
	return (exp);
}

int	count_strings(char **token)
{
	int	i;

	i = 0;
	while (token[i])
		i++;
	return (i);
}

int	*locate_c(char *token, char c)
{
	int	i;
	int	j;
	int	*index_tab;

	i = 0;
	j = 0;
	while ((token[i]) && c)
	{
		if (token[i] == c)
			j++;
		i++;
	}
	index_tab = ft_calloc(j + 1, sizeof(int));
	i = 0;
	j = 0;
	while (token[i] && c)
	{
		if (token[i] == c)
		{
			index_tab[j] = i;
			j++;
		}
		i++;
	}
	return (index_tab);
}

char	*remove_c(char *str, char c)
{
	int		i;
	int		j;
	int 	*index_tab;
	int		nb_index;
	char	*new_str;

	i = 0;
	j = 0;
	index_tab = locate_c(str, c);
	nb_index = 0;
	while (index_tab[nb_index])
		nb_index++;
	new_str = ft_calloc(ft_strlen(str) - nb_index + 1, sizeof(char));
	while (str[i])
	{
		if (i == index_tab[j])
		{
			i++;
			j++;
		}
		if (str[i])
		{
			new_str[i - j] = str[i];
			i++;
		}
	}
	free (index_tab);
	return (new_str);
}
