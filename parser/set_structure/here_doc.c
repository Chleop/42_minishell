/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:46:43 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/10 19:24:39 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*open_here_file(t_data *data, int *fd)
{
	char	*here_file;
	char	*itoa;
	char	*temp;
	char	*nr;
	int		i;

	here_file = ft_strdup("Here_Doc_1");
	while (access(here_file, F_OK) == 0)
	{
		temp = here_file;
		i = 0;
		while (!ft_isdigit(here_file[i]))
			i++;
		nr = ft_substr(here_file, i, ft_strlen(here_file) + 1 - i);
		itoa = ft_itoa(ft_atoi(nr) + 1);
		free_string(nr);
		here_file = ft_strjoin("Here_Doc_", itoa);
		free_string(itoa);
		free_string(temp);
	}
	*fd = open(here_file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (!fd)
		ft_error2(strerror(errno), here_file, data, 1);
	data->here_doc = ft_strdup(here_file);
	return (here_file);
}

void	read_here_doc(t_data *data, char **token, int quoted, int fd)
{
	char	*input;
	char	*temp;
	
	input = NULL;
	while (1)
	{
		input = readline("heredoc> ");
		if (!ft_strncmp(input, *token, ft_strlen((*token) + 1)))
			return ;
		printf("input: %s\n", input);	
		if (quoted)
		{
			temp = input;
		 	input = expand(data, *token);
		 	printf("input: %s\n", input);
			free_string(temp);
		}
		ft_putstr_fd(input, fd);
		ft_putstr_fd("\n", fd);
	}
}

char	*get_here_file(t_data *data, char **token)
{
	char	*temp;
	int		fd;
	int		quoted;
	char	*here_file;

	quoted = is_quoted(*token);
	if (quoted)
	{
		temp = *token;
		*token = remove_c(*token, quoted);
		free_string(temp);
	}
	here_file = open_here_file(data, &fd);
	read_here_doc(data, token, quoted, fd);
	close (fd);
	return (here_file);
}
