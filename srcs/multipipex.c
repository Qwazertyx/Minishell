#include "../incl/minishell.h"

//tab->cmd[i]

void	callerror(const char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

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
		callerror("wait");
	}
}
/*
int	multipipextest(t_var *tab, int nb)
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
int	multipipex(t_var *tab, int nb)
{
	int		fd[2];
	pid_t	pid;
	int		i;

	printf("test1\n");
	i = 0;
	if (pipe(fd) == -1)
		callerror("pipe");
	pid = fork();
	if (pid < 0)
		callerror("fork");
	if (pid > 0)
	{
		printf("test2\n");
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		waitpid(pid, NULL, 0);
		printf("test3\n");
	}
	if (pid == 0)
	{
		printf("test4\n");
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		ft_choice(tab, i);
		printf("test5\n");
		callerror("error");
	}
	i++;
	while (i < nb - 1)
	{
		printf("boucle %d sur %d\n", i, nb - 2);
		redir(tab, i++);
	}
	dup2(fd[1], STDOUT_FILENO);
	printf("---------------------\n");
	ft_choice(tab, i);
	printf("---------------------\n");
}
