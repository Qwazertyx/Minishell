#include "../incl/minishell.h"

int	execmaster(char **maincmd, char **env)
{
	if (!maincmd[0] || !maincmd[0][0])
		return (0);
	if (env[0] && path(maincmd[0], env))
	{
		if (execve(path(maincmd[0], env), maincmd, env) == -1)
			perror("error execve:");
	}
	else
		errorcmd(maincmd[0]);
	exit(0);
}
