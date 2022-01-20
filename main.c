#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	**token;
	t_data	data;
	int		ret;

	if ((argc > 1) || (argv[1]))
		ft_exit(0, "Error: too many arguments");
	input = NULL;
	token = NULL;
	data.envp = envp;
	// data->env doit etre malloc -- voir code Amber
	while (42)
	{
		// ft_putstr_fd("minishou:~$ ", 1);
		// input = get_next_line(0);
		input = readline("our_minishell:~$ ");
		add_history(input);
		if (input)
			token = lexer(input, envp);
		if (token)
			ret = parse(&data, token);
		
		ft_free(&data, token);
	}
	ft_exit(1, NULL);
	return (0);
}
