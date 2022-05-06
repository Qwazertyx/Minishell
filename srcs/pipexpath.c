#include "../incl/minishell.h"

char	**get_paths(char **envp)
{
	char	**paths;
	int		i;

	i = 0;
	while (envp[i] && !ft_strnstr(envp[i], "PATH", 4))
		i++;
	if (!envp[i])
		return (0);
	paths = ft_split(envp[i] + 5, ':');
	return (paths);
}

char	*path(char *cmd, char **env)
{
	char	**paths;
	char	*path;
	char	*slash;
	int		i;

	i = 0;
	if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
		return (cmd);
	paths = get_paths(env);
	if (!paths)
		return (0);
	i = -1;
	while (paths[++i])
	{
		slash = ft_strjoin(paths[i], "/");
		path = ft_joins(slash, cmd);
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
