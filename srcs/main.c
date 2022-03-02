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

void	free_tab(char ***a)
{
	int	i;
	int	j;

	i = 0;
	while (a[i])
	{
		j = -1;
		while (a[i][++j])
			free(a[i][j]);
		free(a[i]);
		i++;
	}
	free(a);
}

void	ft_while(char **env)
{
	char	*a;
	char	*tmp;
	char	***parsed;
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
	add_history(a);
	parsed = parse(a);
	while (parsed[nb])
	{
		int	j = 0;
		// while (parsed[nb][j])
		// {
		// 	printf("%d %d %s\n", nb, j, parsed[nb][j]);
		// 	j++;
		// }
		nb++;
	}
	ft_vpipe(parsed, nb, env);
	wait(NULL);
	free_tab(parsed);
}

void CtrlC(int sig)
{
	fprintf(stdin, "");
}

int	main(int argc, char *argv[], char **env)
{
	(void) argc;
	(void) argv;
	signal(SIGINT, CtrlC);
	while (1)
	{
		ft_while(env);
	}
}
