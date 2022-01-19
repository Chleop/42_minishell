#include "minishell.h"

void	print_char_table(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("tab %d = [%s]\n", i, tab[i]);
		i++;
	}
	return ;
}

void	print_int_table(int *tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("Int tab %d = %d\n", i, tab[i]);
		i++;
	}
	return ;
}

void	print_cmds_and_tokens(t_data *data)
{
	int	i;
	
	i = 0;
	while (i < data->nr_cmds)
	{
		printf("Commande numero %d\n", i + 1);
		print_char_table(data->cmd[i].tok);
		i++;
	}
}
