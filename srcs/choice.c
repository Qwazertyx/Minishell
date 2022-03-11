#include "../incl/minishell.h"

int	ft_strchrquot(char *s, char c, char c2)
{
	int		i;
	char	quot;

	i = 0;
	quot = 0;
	while (s && s[i])
	{
		if (quot == 0 && (s[i] == '\'' || s[i] == '\"'))
			quot = s[i];
		else if (s[i] == quot)
			quot = 0;
		if (quot == 0 && s[i] == c && (c2 == 0 || (s[i + 1] && s[i + 1] == c2)))
			return (i + 1);
		i++;
	}
	return (-1);
}

int	ft_vpipe(t_var *tab, int nb)
{
	// s_chevred(tab[0].cmd[1], env);
	if (nb > 1)
	{

	}
	else
		return (ft_choice(tab, 0));
}

int	ft_strcmp(char *a, char *b)
{
	int	i;

	i = 0;
	while (a[i] && b[i] && a[i] == b[i])
		i++;
	return (a[i] - b[i]);
}

int	ft_choice(t_var *tab, int i)
{
	char	**s;
	int		fd;

	fd = 0;
	printf("cmd = %s\\\n", tab[i].cmd[0]);
	if (ft_strchrquot(tab[i].cmd[1], '>', 0) != -1)
	{
		fd = s_chevred(tab[i].cmd[1]);
		tab[i].cmd[1] = ft_nochevre(tab[i].cmd[1], '>');
		printf("=%s\n", tab[i].cmd[1]);
	}
	if (!ft_strcmp(tab[i].cmd[0], "echo"))
	{
		printf("=enter echo\n\n");
		echomaster(tab[i].cmd[1]);
	}
	else if (!ft_strcmp(tab[i].cmd[0], "cd"))
	{
		printf("=enter cd\n\n");
		mycd(tab[i].cmd);
	}
	else if (!ft_strcmp(tab[i].cmd[0], "pwd"))
	{
		printf("=enter pwd\n\n");
		ft_pwd();
	}
	else if (!ft_strcmp(tab[i].cmd[0], "export"))
	{
		printf("=enter export\n\n");
		exportmaster(tab[i].cmd[1], tab->env);
	}
	else if (!ft_strcmp(tab[i].cmd[0], "unset"))
	{
		printf("=enter unset\n\n");
	}
	else if (!ft_strcmp(tab[i].cmd[0], "env"))
	{
		printf("=enter env\n\n");
		ft_env(env);
	}
	else if (!ft_strcmp(tab[i].cmd[0], "exit"))
	{
		printf("=enter exit\n\n");
		ft_exit(tab, i);
	}
	else if (tab[i].cmd[0] == '\0')
		return (1);
	else
	{
		printf("=enter execve\n\n");
		s = ft_splitve(tab[i].cmd[1], ' ', tab[i].cmd[0]);
		execmaster(s, env);
		free(s);
	}
	return (fd);
}
