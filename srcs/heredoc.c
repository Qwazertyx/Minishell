#include "../incl/minishell.h"

void	ft_while_doublechevre(int *pipes[2], char ***file, int i, int j)
{
	char	*read;

	read = readline("> ");
	while (ft_strcmp(read, &file[i][j][2]))
	{
		if (j == whoislastdouble(file[i]))
			ft_putendl_fd(read, pipes[1][i]);
		free(read);
		read = readline("> ");
	}
	free(read);
	close(pipes[1][i]);
	close(pipes[0][i]);
}

int	ft_doublechevre(int *pipes[2], char ***file)
{
	int		i;
	int		j;

	i = -1;
	while (file[++i])
	{
		j = -1;
		while (file[i][++j])
			if (file[i][j][0] == '<')
				ft_while_doublechevre(pipes, file, i, j);
	}
	return (0);
}

void	fill_pipes(char ***file, int *pipes[2])
{
	int	i;
	int	pip[2];

	i = 0;
	while (file[i])
		i++;
	pipes[0] = malloc((i + 1) * sizeof(int));
	pipes[1] = malloc((i + 1) * sizeof(int));
	i = -1;
	while (file[++i])
	{
		pipe(pip);
		pipes[0][i] = pip[0];
		pipes[1][i] = pip[1];
	}
	pipes[0][i] = 0;
	pipes[1][i] = 0;
}

int	*ft_heredoctest(t_var *p, char ***file)
{
	int		i;
	int		*pipes[2];
	pid_t	pid;

	fill_pipes(file, pipes);
	pid = fork();
	if (!pid)
	{
		signal(SIGINT, sig_heredoc);
		exit(ft_doublechevre(pipes, file));
	}
	else
	{
		i = -1;
		while (file[++i])
			close(pipes[1][i]);
		free(pipes[1]);
		return (pipes[0]);
	}
}
