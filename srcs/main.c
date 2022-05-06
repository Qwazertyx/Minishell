#include "../incl/minishell.h"

void	ft_useread(t_var *parsed, char *a)
{
	pid_t	pid;
	int		nb;

	nb = 0;
	if (is_input(a))
	{
		parsed = parse(a, parsed);
		if (!parsed)
			return ;
		while (parsed->cmd[nb])
			nb++;
		pid = ft_vpipe(parsed, nb);
		if (pid)
		{
			waitpid(pid, &nb, 0);
			if (g_exit != 130 && g_exit != 131)
				g_exit = WEXITSTATUS(nb);
		}
		dprintf(2, "%d\n", g_exit);
		while (wait(NULL) != -1)
			;
		free_struc(parsed, 0);
	}
}

void	ft_while(t_var *parsed)
{
	char	*a;
	char	*tmp;
	int		nb;
	pid_t	pid;

	nb = 0;
	tmp = ft_prompt();
	a = readline(tmp);
	free(tmp);
	if (!a)
	{
		ft_putstr_fd("  \b\bexit\n", 2);
		exit(0);
	}
	if (a[0])
	{
		add_history(a);
		ft_useread(parsed, a);
	}
	else
		free(a);
}

char	**prep_env(char **envp)
{
	char	**env;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	env = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (envp[i])
	{
		if (ft_startcompare("SHLVL", envp[i]))
			env[i] = ft_joinc(ft_strdup("SHLVL="),
					ft_atoi(ft_getenv("SHLVL", envp)) + 49);
		else
			env[i] = ft_strdup(envp[i]);
		i++;
	}
	env[i] = 0;
	return (env);
}

int	main(int argc, char *argv[], char **envp)
{
	int		i;
	char	**env;
	t_var	struc;

	env = prep_env(envp);
	struc.env = &env;
	(void) argc;
	(void) argv;
	while (1)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, ctrl_bs);
		ft_while(&struc);
	}
}
