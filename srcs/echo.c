#include "../incl/minishell.h"
/*
char	**get_paths(char **envp)
{
	char	**paths;
	int		i;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	paths = ft_split(envp[i] + 5, ':');
	return (paths);
}

char	*path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*slash;
	int		i;

	i = 0;
	if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
		return (cmd);
	paths = get_paths(envp);
	i = -1;
	while (paths[++i])
	{
		slash = ft_strjoin(paths[i], "/");
		path = ft_strjoin(slash, cmd);
		free(slash);
		if (!access(path, F_OK))
		{
			free_split(paths);
			return (path);
		}
		free(path);
	}
	free_split(paths);
	return (0);
}

int	echospecial(char *cmd, char **envp, int i)
{
	int		j;
	char	*toech;

	j = 0;
	while (cmd[i + j] != ' ')
		j++;
	toech = malloc((j + 1) * sizeof(char));
	toech[0] = cmd[i];
	j = 0;
	while (cmd[i + j] != ' ')
	{
		toech[j] = cmd[i + j];
		j++;
	}
	toech[j] == 0;
	printf("|%s|fewewewe", toech);
	return (j);
}

int	echomaster(char *cmd, char **envp)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '$')
		{
			i += echospecial(cmd, envp, i + 1);
			i++;
		}
		else
			ft_putchar(cmd[i]);
		i++;
	}
	return (1);
}
*/

int	echospecial(char *cmd, char **envp, int i)
{
	int		j;
	char	*toech;

	j = 0;
	while (cmd[i + j] != ' ')
		j++;
	toech = malloc((j + 1) * sizeof(char));
	toech[0] = cmd[i];
	j = 0;
	while (cmd[i + j] != ' ')
	{
		toech[j] = cmd[i + j];
		j++;
	}
	toech[j] == 0;
	printf("|%s|", toech);
	return (j);
}

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	nparam(char *cmd)
{
	if (cmd[0] && cmd[1] && cmd[2]
		&& cmd[0] == '-' && cmd[1] == 'n' && cmd[2] == ' ')
		return (3);
	return (0);
}

int	echomaster(char *cmd, char **envp)
{
	int	i;
	int	quot;

	i = nparam(cmd);
	quot = 0;
	while (cmd[i])
	{
		if (cmd[i] == '$')
		echospecial
		else if (cmd[i] == '\'' && quot == 0)
			quot = 1;
		else if (cmd[i] == '\"' && quot == 0)
			quot = 2;
		else if ((cmd[i] == '\"' && quot == 2) || (cmd[i] == '\'' && quot == 1))
			quot = 0;
		else if ((cmd[i] == '\"' && quot == 1) || (cmd[i] == '\'' && quot == 2)
			|| (cmd[i] != '\"' && cmd[i] != '\''))
			ft_putchar(cmd[i]);
		i++;
	}
	if (!nparam(cmd))
		write(1, "\n", 1);
	return (1);
}
