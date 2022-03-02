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

void	ft_while(char **env)
{
	char	*a;
	char	*tmp;
	char	**parsed;

	tmp = ft_prompt();
	a = readline(tmp);
	free(tmp);
	add_history(a);
	parsed = parse(a);
	// int	j = 0;
	// while (parsed[j])
	// {
	// 	printf("%d %s\n", j, parsed[j]);
	// 	j++;
	// }
	execmaster(parsed, env);
	wait(NULL);
}

int	main(int argc, char *argv[], char **env)
{
	(void) argc;
	(void) argv;
	while (1)
	{
		ft_while(env);
	}
}
