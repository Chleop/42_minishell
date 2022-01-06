#include "minishell.h"

int	main(int argc, char **argv)
{
	char	*input;
	char	**token;

	if (argc > 1)
		printf("Error: too many arguments");
	if (ft_strncmp(argv[0], "./minishell", 11))
		printf("Error: ");
	while (42)
	{
		ft_putstr_fd("minishou:~$ ", 1);
		input = get_next_line(0);
		token = split_into_token(input);
		free (input);
		print_table(token);
		ft_del_stringtab(&token);
	}
	return (0);
}
