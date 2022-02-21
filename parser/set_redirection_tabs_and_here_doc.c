/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection_tabs_and_here_doc.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:46:43 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/21 16:38:52 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_here_file(t_data *data, int *fd)
{
	char	*itoa;
	char	*temp;
	char	*nr;
	int		i;

	data->here_doc = ft_strdup("Here_Doc_1");
	while (access(data->here_doc, F_OK) == 0)
	{
		temp = data->here_doc;
		i = 0;
		while (!ft_isdigit(data->here_doc[i]))
			i++;
		nr = ft_substr(data->here_doc, i, ft_strlen(data->here_doc) + 1 - i);
		itoa = ft_itoa(ft_atoi(nr) + 1);
		free_string(&nr);
		data->here_doc = ft_strjoin("Here_Doc_", itoa);
		free_string(&itoa);
		free_string(&temp);
	}
	*fd = open(data->here_doc, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (!fd)
		ft_error2(strerror(errno), data->here_doc, 1);
}

void	read_here_doc(t_data *data, char **token, int fd)
{
	char	*input;

	input = NULL;
	while (1)
	{
		g_lobal.g_sig = -42;
		input = readline(GREEN "heredoc> " RESET);
		if (!input)
		{
			g_lobal.here_d = 1;
			ft_printf("warning: here-document ended by end-of-file\n", 1);
			return ;
		}
		if (!ft_strncmp(input, *token, ft_strlen(*token) + 1))
		{
			free_string(&input);
			return ;
		}
		if (ft_strchr(input, '$'))
			manage_expansions(data, &input, HERE_END);
		ft_putstr_fd(input, fd);
		ft_putstr_fd("\n", fd);
		free_string(&input);
	}
}

void	get_here_file(t_data *data, char **token)
{
	char	*temp;
	int		fd;
	int		quoted;

	quoted = is_quoted(*token);
	if (quoted)
	{
		temp = *token;
		remove_quotes(token);
		free_string(&temp);
	}
	open_here_file(data, &fd);
	read_here_doc(data, token, fd);
	close (fd);
}

int	set_redirections_tabs(t_data *data, char **token, int n, int qualif)
{
	if (qualif == HERE_END)
	{
		get_here_file(data, token);
		add_tab(&(data->cmd[n].i), &(data->cmd[n].nr_in), data->here_doc);
	}
	else if (qualif == RED_IN)
		add_tab(&(data->cmd[n].i), &(data->cmd[n].nr_in), *token);
	else
	{
		add_tab(&(data->cmd[n].o), &(data->cmd[n].nr_out), *token);
		if (qualif == RED_OUT_S)
			add_int(&(data->cmd[n].type), data->cmd[n].nr_out, 1);
		else
			add_int(&(data->cmd[n].type), data->cmd[n].nr_out, 2);
	}
	return (1);
}
