#include "../incl/minishell.h"

void	modify_oldpwd(char **env, char *pwd, t_var *p)
{
	int	i;

	i = 0;
	while (env[i] && !ft_startcompare("OLDPWD", env[i]))
		i++;
	if (!env[i])
		return ;
	free(env[i]);
	env[i] = ft_joinsfree2("OLDPWD=", pwd);
	if (!env[i])
		exit_export(p, i);
}

void	modify_pwd(char **env, char *pwd, t_var *p)
{
	int	i;

	i = 0;
	while (env[i] && !ft_startcompare("PWD", env[i]))
		i++;
	if (!env[i])
		return ;
	free(env[i]);
	env[i] = ft_joinsfree2("PWD=", getcwd(NULL, 0));
	if (!env[i])
		exit_export(p, i);
	modify_oldpwd(env, pwd, p);
}

void	mycd(char **path, char **env)
{
	int		i;

	if (path[1])
	{
		i = 0;
		while (path[1][i + 1])
			i++;
		if (path[1][i] && path[1][i] == ' ')
			path[1][i] = 0;
		if (chdir(path[1]) != 0)
		{
			ft_putstr_fd("Minishell: cd: ", 2);
			perror(path[1]);
			g_exit = 1;
		}
	}
	else
	{
		if (chdir(ft_getenv("HOME", env)) != 0)
		{
			ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
			g_exit = 1;
		}
	}
}

void	cd(char **path, char **env, t_var *p)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (path[1] && path[1][0] == '-' && !path[1][1])
	{
		if (chdir(ft_getenv("OLDPWD", env)) != 0)
		{
			ft_putstr_fd("Minishell: cd: OLDPWD not set\n", 2);
			g_exit = 1;
		}
	}
	else
		mycd(path, env);
	if (g_exit != 1)
		modify_pwd(env, oldpwd, p);
	else
		free(oldpwd);
}
