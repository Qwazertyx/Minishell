#include "../incl/minishell.h"

void	**envcreate(char **env, char **newenv)
{
	int		i;
	int		y;

	i = 0;
	while (env[i])
	{
		y = 0;
		newenv[i] = malloc((ft_strlen(env[i]) + 1) * sizeof(char));
		while (env[i][y])
		{
			newenv[i][y] = env[i][y];
			y++;
		}
		newenv[i][y] = 0;
		i++;
	}
	y = 0;
	newenv[i] = 0;
	i++;
	newenv[i] = 0;
}

char	**exportservant(char *var, char **env)
{
	int		i;
	int		y;
	char	**newenv;

	i = 0;
	while (env[i])
		i++;
	newenv = malloc((i + 2) * sizeof(char *));
	envcreate(env, newenv);
	i = 0;
	y = 0;
	while (newenv[i])
		i++;
	while (var[y])
	{
		newenv[i][y] = var[y];
		y++;
	}
	printf("ici\n");
	newenv[i][y] = 0;
	i++;
	newenv[i] = 0;
	printf("la\n");
	i = 0;
	while (newenv[i])
		printf("%s\n", newenv[i++]);
	printf("%s\n", newenv[i++]);
	printf("%s\n", newenv[i++]);
	return (newenv);
}

char	**exportmaster(char *var, char **env)
{
	int	i;

	i = 0;
	if (!var)
	{
		while (env[i])
		{
			write(1, "declare -x ", 11);
			ft_putstr_fd(env[i], 1);
			write(1, "\n", 1);
			i++;
		}
	}
	else
	{
		
	}
		env = exportservant(var, env);
	return (env);
}
/*
char	**exportmaster(char *var, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%d %s\n", i, env[i]);
		i++;
	}
	printf("%d %s\n", i, env[i]);
	i++;
	while (i < 60)
	{
		printf("%d %s\n", i, env[i]);
		i++;
	}

}
*/
