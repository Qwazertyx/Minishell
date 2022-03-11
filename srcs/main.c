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
	while (a && a[i].cmd)
	{
		j = -1;
		while (a[i].cmd && a[i].cmd[++j])
			free(a[i].cmd[j]);
		free(a[i].cmd);
		// if (a[i].output)
		// 	free(a[i].output);
		i++;
	}
	free(a);
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
		parsed = parse(a);
		while (parsed[nb].cmd)
		{
			// int	j = 0;
			// while (parsed[nb].cmd[j])
			// {
			// 	printf("%d %d %s\n", nb, j, parsed[nb].cmd[j]);
			// 	j++;
			// }
			nb++;
		}
		nb = ft_vpipe(parsed, nb, parsed->env);
		wait(NULL);
		free_tab(parsed);
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
	}
}
