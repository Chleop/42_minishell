/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:33:03 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/08 17:53:36 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

enum	BI
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
};

typedef struct	s_envp
{
	char			*name;
	char			*var;
	int				printed;
	struct s_envp	*next;
	struct s_envp	*previous;
}	t_envp;

typedef struct s_cd
{
	char	*oldpwd;
	char	*current;
	char	*path;
	int		level;
}	t_cd;

//envp functions
int		init_envp(t_data *data, char *envp[]);
void	free_envp(t_data *data);
t_envp	*new_item(char *string);
void	add_item_back(t_envp **list, t_envp *new);
int		size_list(t_envp *head);
void	add_to_envp(t_envp *envp, char *var);
void	remove_from_envp(t_envp *envp, char *name);
void	convert_envp(t_envp *envp, char ***table);

//execution functions
int		exec_prefork_builtins(t_cmd *cmd);
int		fork_function(t_cmd *cmd);
int		exec_non_builtins(int process, t_cmd *cmd);
int		exec_builtins(t_cmd *cmd);
int		init_pipes(t_data *data);
void	pipe_function(t_cmd *cmd);
void	close_all_except_two(t_data *data, int pipe);

//redirection functions
int		redirect_io(t_cmd *cmd);
void	reverse_redirection(t_cmd *cmd, int in, int out);

//built in functions
void	ft_echo(t_cmd *cmd);
void	ft_env(t_cmd *cmd);
void	ft_export_prefork(t_cmd *cmd);
void	ft_export_fork(t_cmd *cmd);
int		check_identifier(char *id, int code);
void	ft_unset(t_cmd *cmd);
void	ft_pwd(void);
void	ft_cd(t_cmd *cmd);
int		init_cd(t_cmd *cmd, t_cd **cd);
char	*get_var(t_envp *envp, char *name);
void	handle_dots(t_cmd *cmd, t_cd *cd);
void	chdir_path(t_data *data, t_cd *cd);
char	*set_curpath(char *string);
void	exit_error_cd(char **dir_tab, char *string1, char *string2);
void	ft_exit(t_cmd *cmd);

//exit functions
void	free_io(t_cmd *cmd);
void	free_dir_tab(char **dir_tab);
void	finish_up(t_data *data);
void	free_string(char *string);
void	free_node_envp(t_envp *envp);

#endif