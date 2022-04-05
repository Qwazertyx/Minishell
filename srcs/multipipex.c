#include "../incl/minishell.h"

//tab->cmd[i]

void	callerror(const char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

/*
int	multipipepxxtest(t_var *tab, int nb)
{
	int	i;
	int	fd[2];

	//fd[0] = open(STDIN_FILENO, O_RDONLY);
	//fd[1] = open(STDOUT_FILENO, O_WRONLY | O_CREAT | O_TRUNC);
	//if (fd[0] == -1 || fd[1] == -1)
	//	callerror("open");
	//dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	i = 0;
	while (i < nb - 1)
		redir(tab, i++);
	dup2(fd[1], STDOUT_FILENO);
	ft_choice(tab, i);
	return (0);
}
*/

static void	redir(t_var *tab, int i)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		callerror("pipe");
	pid = fork();
	if (pid < 0)
		callerror("fork");
	if (pid > 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		waitpid(pid, NULL, 0);
	}
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		ft_choice(tab, i);
		exit(1);
	}
}
	//pid = fork();
		//if (pid < 0)
		//	callerror("fork");
		//if (pid > 0)
		//	waitpid(pid, NULL, 0);
int	multipipex(t_var *tab, int nb)
{
	int		fd[2];
	pid_t	pid;
	int		i;

	pid = fork();
	if (!pid)
	{
		i = 0;
		while (i < nb - 1)
		{
			printf("boucle %d sur %d\n", i + 1, nb - 1);
			redir(tab, i++);
		}
		ft_choice(tab, i);
	}
	else
		waitpid(pid, NULL, 0);
	return (0);
}

static void	redir2(t_var *tab, int i)
{
	int		fd[2];
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		callerror("fork");
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		ft_choice(tab, i);
		exit(1);
	}
}

int	multipipex2(t_var *tab, int nb)
{
	int		fd[2];
	int		i;
	int		status;

	if (pipe(fd) == -1)
		callerror("pipe");
	i = 0;
	while (i < nb - 1)
	{
		printf("boucle %d sur %d\n", i + 1, nb - 1);
		redir2(tab, i++);
	}
	close(fd[0]);
	close(fd[1]);
	i = 0;
	while (i < nb - 1)
		waitpid(-1, &status, 0 * i++);
	ft_choice(tab, i);
	waitpid(-1, &status, 0 * i++);
	return (0);
}
