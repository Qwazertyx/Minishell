#include "../incl/minishell.h"

	// dprintf(1, "PATH:%s\n", path(maincmd[0], envp));
		//if (execve(path(maincmd[0], envp), maincmd, envp) == -1)
	//	int j = 0;
	//	while(maincmd[j])
	//		dprintf(2, "line=%s", maincmd[j++]);
int	execmaster(char **maincmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid != 0)
		return (0);
	if (maincmd[0] && path(maincmd[0], envp))
	{
		if (execve(path(maincmd[0], envp), maincmd, envp) == -1)
			perror("error execve:");
	}
	else
		errorcmd(maincmd);
	exit(0);
}
