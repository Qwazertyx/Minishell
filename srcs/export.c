#include "../incl/minishell.h"
/*
void	**envcreate(char **env, char **newenv)
{
	int		i;
	int		y;
	printf("entree create\n");
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

void	**exportservant(char *var, t_var *env)
{
	int		i;
	int		y;
	char	**newenv;

	printf("entree servant\n");
	i = 0;
	while (env[i])
		i++;
	newenv = malloc((i + 2) * sizeof(char *));
	i = 0;
	while (tab->env[i])
		newenv[i] = ft_strdup()
	free(tab->env[i]);
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
	newenv[i][y] = 0;
	i++;
	newenv[i] = 0;
	i = 0;
	while (newenv[i])
		printf("%s\n", newenv[i++]);
}
*/
void	**envcpy(char *var, t_var *data, char **newenv)
{
	int	i;

	printf("entree cpy\n");
	i = 0;
	while (newenv[i])
	{
		data->env[i] = ft_strdup(newenv[i]);
		i++;
	}
	data->env[i] = ft_strdup(var);
	data->env[i] = 0;
	free(newenv);
	printf("sortie cpy\n");
}

void	**exportservant(char *var, t_var *tab)
{
	int		i;
	char	**newenv;

	printf("entree servant\n");
	i = 0;
	while (tab->env[i])
		i++;
	newenv = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (tab->env[i])
	{
		newenv[i] = ft_strdup(tab->env[i]);
		i++;
	}
	newenv[i] = 0;
	free(tab->env[i]);
	tab->env[i] = malloc((i + 2) * sizeof(char *));
	envcpy(var, tab, newenv);
	printf("sortie servant\n");
}

void	**exportmaster(char *var, t_var *tab)
{
	int	i;

	i = 0;
	printf("entree master\n");
	if (!var)
	{
		while (tab->env[i])
		{
			write(1, "declare -x ", 11);
			ft_putstr_fd(*tab->env[i], 1);
			write(1, "\n", 1);
			i++;
		}
	}
	else
	{
		exportservant(var, tab);
	}
	printf("sortie master\n");
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
