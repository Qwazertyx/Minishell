#include "../incl/minishell.h"

void	ft_vpipe(char ***tab, int nb, char **env)
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

void	*ft_choice(char ***tab, char **env, int i)
{
	printf("cmd = %s\n", tab[i][0]);
	if (!ft_strcmp(tab[i][0], "echo"))
	{
		printf("=enter echo\n\n");
		echomaster(tab[i][1], env);
	}
	else if (!ft_strcmp(tab[i][0], "cd"))
	{
		printf("=enter cd\n\n");
	}
	else if (!ft_strcmp(tab[i][0], "pwd"))
	{
		printf("=enter pwd\n\n");
	}
	else if (!ft_strcmp(tab[i][0], "export"))
	{
		printf("=enter export\n\n");
	}
	else if (!ft_strcmp(tab[i][0], "unset"))
	{
		printf("=enter unset\n\n");
	}
	else if (!ft_strcmp(tab[i][0], "env"))
	{
		printf("=enter env\n\n");
	}
	else if (!ft_strcmp(tab[i][0], "exit"))
	{
		ft_exit(tab, i);
		printf("=enter exit\n\n");
	}
	else if (tab[i][0][0] == '\0')
		return (0);
	else
	{
		printf("=enter execve\n\n");
		execmaster(tab[i], env);
	}
}
