#include "minishell.h"

int	main(int argc, char **envp)
{
	char	*input;
	char	**token;
	t_data	*data;
	int		ret;

	if (argc > 1)
		ft_exit(0, "Error: too many arguments");
	input = NULL;
	token = NULL;
	data = (t_data *)malloc(sizeof(t_data) * 1);
	if (!data)
		perror("Error: malloc failed");
	data->envp = envp;
	// data->env doit etre malloc -- voir code Amber
	while (42)
	{
		ft_putstr_fd("minishou:~$ ", 1);
		input = get_next_line(0);
		if (input)
			token = split_into_token(input, envp);
		if (token)
			print_char_table(token);
		if (token)
			ret = parse(data, token);
		if (ret)
			ft_del_stringtab(&token);
	}
	ft_exit(1, NULL);
	return (0);
}
