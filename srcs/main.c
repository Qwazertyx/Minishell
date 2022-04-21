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

void	free_cmd(char ***cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd && cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			free(cmd[i][j++]);
		}
		free(cmd[i++]);
	}
	free(cmd);
}

void	ft_close(t_var *p)
{
	int	i;

	i = 0;
	while (p->cmd[i])
		close(p->heredocfd[i++]);
	free(p->heredocfd);
}

void	free_struc(t_var *p, int i)
{
	ft_close(p);
	free_cmd(p->cmd);
	free_cmd(p->chevred);
	free_cmd(p->chevreg);
	if (i == 1)
		free_cmd(p->env);
}

void	ft_while(t_var *parsed)
{
	char	*a;
	char	*tmp;
	int		nb;

	nb = 0;
	tmp = ft_prompt();
	tmp = ft_strjoin2("🎃 ", tmp);
	a = readline(tmp);
	free(tmp);
	if (a == 0)
	{
		printf("\b\bexit\n");
		exit(0);
	}
	if (a[0])
	{
		add_history(a);
		if (is_input(a))
		{
			parsed = parse(a, parsed);
			if (!parsed)
				return ;
			while (parsed->cmd[nb])
				nb++;
			ft_vpipe(parsed, nb);
			wait (NULL);
			free_struc(parsed, 0);
		}
	}
	else
		free(a);
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
		if (ft_startcompare("SHLVL", envp[i]))
			env[i] = ft_joinc(ft_strdup("SHLVL="),
					ft_atoi(ft_getenv("SHLVL", envp)) + 49);
		else
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
