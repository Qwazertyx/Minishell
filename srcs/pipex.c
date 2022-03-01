#include "../incl/minishell.h"

void	child_one(int *pipefd, int *fd, char **av, char **envp)
{
	char	**cmd;
	pid_t	c_pid;

	c_pid = fork();
	if (c_pid < 0)
		terminate();
	if (c_pid == 0)
	{
		fd[0] = open(av[1], O_RDONLY);
		if (fd[0] < 0)
			terminate();
		cmd = ft_split(av[2], ' ');
		close(pipefd[0]);
		dup2(fd[0], STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		if (cmd[0] && path(cmd[0], envp))
		{
			execve(path(cmd[0], envp), cmd, envp);
			free_split(cmd);
		}
		else
			errorcmd(cmd);
	}
}

void	child_two(int *pipefd, int *fd, char **av, char **envp)
{
	char	**cmd;
	pid_t	c_pid;

	c_pid = fork();
	if (c_pid < 0)
		terminate();
	if (c_pid == 0)
	{
		fd[1] = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd[1] < 0)
			terminate();
		cmd = ft_split(av[3], ' ');
		close(pipefd[1]);
		dup2(fd[1], STDOUT_FILENO);
		dup2(pipefd[0], STDIN_FILENO);
		if (cmd[0] && path(cmd[0], envp))
		{
			execve(path(cmd[0], envp), cmd, envp);
			free_split(cmd);
		}
		else
			errorcmd(cmd);
	}
}

int	pipex(int ac, char **av, char **envp)
{
	int	pipefd[2];
	int	fd[2];
	int	status;

	if (ac != 5)
		return (write(2, "usage: ./pipex [file1] [cmd1] [cmd2] [file2]\n", 45));
	if (pipe(pipefd) < 0)
		terminate();
	child_one(pipefd, fd, av, envp);
	child_two(pipefd, fd, av, envp);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(-1, &status, 0);
	waitpid(-1, &status, 0);
	return (0);
}
