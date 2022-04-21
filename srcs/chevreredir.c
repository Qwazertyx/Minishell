#include "../incl/minishell.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	c;

	c = 0;
	if (s)
	{
		while (s[c])
		{
			write(fd, &s[c], 1);
			c++;
		}
		write(fd, "\n", 1);
	}
}

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

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	write(fd, s, i);
	write(fd, "\n", 1);
}
char	*doublechevre(char **file, t_var *tab, int i)
{
	int		y;
	char	*stop;
	char	*read;
	char	**heredoc;
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
	read = readline(0);
	while (ft_strcmp(read, stop))
	{
		if (i == whoislastdouble(file))
			ft_putendl_fd(read, pipefd[1]);
		free(read);
		read = readline(0);
	}
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	free(stop);
	return (read);
}

int	ft_chevreg(char **file, t_var *tab)
{
	int		i;
	int		fd;

	dprintf(2, "last: %d == %s\n", whoislastdouble(file), file[whoislastdouble(file)]);
	i = 0;
	while (file[i])
	{
		if (file[i][0] != '<')
		{
			fd = open(&file[i][2], O_RDONLY);
			close(fd);
		}
		else if (file[i][0] == '<')
			doublechevre(file, tab, i);
		i++;
	}
	if (file[i - 1][0] != '<')
	{
		fd = open(&file[i - 1][2], O_RDONLY);
		if (fd < 0)
			terminate();
		dup2(fd, STDIN_FILENO);
	}
	return (0);
}
