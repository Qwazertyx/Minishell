#include "../incl/minishell.h"

char	*ft_strdup(char *a)
{
	int		i;
	char	*s;

	i = 0;
	while (a[i])
		i++;
	s = malloc(i + 1);
	i = 0;
	while (a[i])
	{
		s[i] = a[i];
		i++;
	}
	return (s);
}

int	main(int argc, char *argv[], char **env)
{
	char	*a;
	char	*tmp;
	char	**parsed;

	(void) argc;
	(void) argv;
	while (1)
	{
		tmp = ft_prompt();
		a = readline(tmp);
		free(tmp);
		if (a)
			parsed = parse(a);
		char *maincmd[2] = {"ls", "-la"};
		execmaster(maincmd, env);
	}
}
