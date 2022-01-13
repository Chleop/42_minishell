#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	**token;
	// t_data	*data;

	if (argc > 1)
		perror("Error: too many arguments");
	if (ft_strncmp(argv[0], "./minishell", 11))
		perror("Error: ");
	// data = (t_data *)malloc(sizeof(t_data) * 1);
	// if (!data)
	// 	perror("Error: ");
	// data->envp = envp;
	while (42)
	{
		ft_putstr_fd("minishou:~$ ", 1);
		input = get_next_line(0);
		token = split_into_token(input, envp);
		print_char_table(token);
		parse(token);
		ft_del_stringtab(&token);
	}
	return (0);
}
