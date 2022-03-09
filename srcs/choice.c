#include "../incl/minishell.h"

void	ft_vpipe(t_var *tab, int nb, char **env)
{
	if (nb > 1)
	{

	}
	else
		ft_choice(tab, env, 0);
}

int	ft_strcmp(char *a, char *b)
{
	int	i;

	i = 0;
	while (a[i] && b[i] && a[i] == b[i])
		i++;
	return (a[i] - b[i]);
}

void	ft_choice(t_var *tab, char **env, int i)
{
	char	**s;

	printf("cmd = %s\n", tab[i].cmd[0]);
	if (!ft_strcmp(tab[i].cmd[0], "echo"))
	{
		printf("=enter echo\n\n");
		echomaster(tab[i].cmd[1], env);
	}
	else if (!ft_strcmp(tab[i].cmd[0], "cd"))
	{
		printf("=enter cd\n\n");
		mycd(tab[i].cmd);
	}
	else if (!ft_strcmp(tab[i].cmd[0], "pwd"))
	{
		printf("=enter pwd\n\n");
		ft_pwd(&tab[i]);
	}
	else if (!ft_strcmp(tab[i].cmd[0], "export"))
	{
		printf("=enter export\n\n");
	}
	else if (!ft_strcmp(tab[i].cmd[0], "unset"))
	{
		printf("=enter unset\n\n");
	}
	else if (!ft_strcmp(tab[i].cmd[0], "env"))
	{
		printf("=enter env\n\n");
		ft_env(env, tab);
	}
	else if (!ft_strcmp(tab[i].cmd[0], "exit"))
	{
		printf("=enter exit\n\n");
		ft_exit(tab, i);
	}
	else if (tab[i].cmd[0] == '\0')
		return ;
	else
	{
		printf("=enter execve\n\n");
		s = ft_splitve(tab[i].cmd[1], ' ', tab[i].cmd[0]);
		execmaster(s, env);
		free(s);
	}
}
