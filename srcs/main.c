#include "../incl/minishell.h"

char	*ft_strdup(char *a)
{
	int		i;
	char	*s;

	i = 0;
	while (a[i])
		i++;
	s = malloc(i + 1);
	i = -1;
	while (a[++i])
		s[i] = a[i];
	s[i] = '\0';
	return (s);
}

void	free_tab(t_var *a)
{
	int	i;
	int	j;

	i = 0;
	while (a && a->cmd[i])
	{
		j = 0;
		while (a->cmd[i] && a->cmd[i][j])
			free(a->cmd[i][j++]);
		free(a->cmd[i]);
		i++;
	}
}

void	ft_while(t_var *parsed)
{
	char	*a;
	char	*tmp;
	int		nb;

	nb = 0;
	tmp = ft_prompt();
	a = readline(tmp);
	free(tmp);
	if (a == 0)
	{
		printf("\b\bexit\n");
		exit(0);
	}
	if (!a[0])
		return ;
	add_history(a);
	if (is_input(a))
	{
		parse(a, parsed);
		while (parsed->cmd[nb])
		{
			int	j = 0;
			while (parsed->cmd[nb][j])
			{
				printf("%d %d %s\n", nb, j, parsed->cmd[nb][j]);
				j++;
			}
			nb++;
		}
		nb = ft_vpipe(parsed, nb);
		wait(NULL);
		free_tab(parsed);
		// int	i = 0;
		// while (parsed->env[0][i])
		// 	printf("%s\n", parsed->env[0][i++]);
		if (nb != 0)
			dup2(nb, 1);
	}
}

void CtrlC(int sig)
{
	(void)sig;
	// printf("\n\033[32m~/Desktop/cursus/minishelldossier/Minishell > \033[0m");
	// fprintf(stdin, "%d", -1);
}

int	main(int argc, char *argv[], char **envp)
{
	int		i;
	char	**env;
	t_var	struc;

	i = 0;
	while (envp[i])
		i++;
	env = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	env[i] = 0;
	struc.env = &env;
	(void) argc;
	(void) argv;
	//signal(SIGINT, CtrlC);
	while (1)
	{
		ft_while(&struc);
		// i = 0;
		// while (struc.env[0][i])
		// 	printf("%s\n", struc.env[0][i++]);
	}
}
