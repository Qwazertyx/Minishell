#include "../incl/minishell.h"

int	whoislastdouble(char **file)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (file[i] && file[i][1])
	{
		if (file[i][0] == '<')
			y = i;
		i++;
	}
	return (y);
}

void	readline_doublechevre(char **file, char *stop, int pipefd[2], int i)
{
	char	*read;

	read = readline("> ");
	while (ft_strcmp(read, stop))
	{
		if (i == whoislastdouble(file))
			ft_putendl_fd(read, pipefd[1]);
		free(read);
		read = readline("> ");
	}
	free(read);
	close(pipefd[1]);
	free(stop);
}

int	doublechevre(char **file, int i)
{
	int		y;
	char	*stop;
	int		pipefd[2];

	y = 0;
	stop = malloc((ft_strlen(file[i]) - 2 + 1) * sizeof(char *));
	while (file[i][y + 2])
	{
		stop[y] = file[i][y + 2];
		y++;
	}
	pipe(pipefd);
	stop[y] = 0;
	readline_doublechevre(file, stop, pipefd, i);
	return (pipefd[0]);
}

int	ft_while_chevreg(char **file, t_var *tab, int i, int j)
{
	int	fd;

	if (file[i][0] != '<')
	{
		fd = open(&file[i][2], O_RDONLY);
		if (fd < 0)
		{
			ft_putstr_fd("Minishell: ", 2);
			perror(&file[i][2]);
			g_exit = 1;
			return (0);
		}
		close(fd);
	}
	else if (!file[i + 1])
	{
		dup2(tab->heredocfd[j], STDIN_FILENO);
		close(tab->heredocfd[j]);
	}
	return (1);
}

int	ft_chevreg(char **file, t_var *tab, int j)
{
	int	i;
	int	fd;
	int	ret;

	i = -1;
	ret = 0;
	while (file[++i])
		if (!ft_while_chevreg(file, tab, i, j))
			return (0);
	if (file[i - 1][0] != '<')
	{
		fd = open(&file[i - 1][2], O_RDONLY);
		if (fd < 0)
		{
			ft_putstr_fd("Minishell: ", 2);
			perror(&file[i - 1][2]);
			g_exit = 1;
			return (0);
		}
		ret = dup(0);
		dup2(fd, STDIN_FILENO);
	}
	return (ret);
}
