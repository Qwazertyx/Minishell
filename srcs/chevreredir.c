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

char	*doublechevre(char **file, t_var *tab, int i)
{
	int		y;
	char	*stop;
	char	*read;
	char	**heredoc;

	y = 0;
	stop = malloc((ft_strlen(file[i]) - 2 + 1) * sizeof(char *));
	while (file[i][y + 2])
	{
		stop[y] = file[i][y + 2];
		y++;
	}
	stop[y] = 0;
	read = readline(0);
	if (i == whoislastdouble(file))
		ft_putstr_fd(read, 3);
	while (ft_strcmp(read, stop))
	{
		read = readline(0);
		if (i == whoislastdouble(file))
			ft_putstr_fd(read, 3);
	}
	free(stop);
	return (read);
}

int	ft_chevreg(char **file, t_var *tab)
{
	int		i;
	int		fd;

	dprintf(2, "last: %d\n == %s\n", whoislastdouble(file), file[whoislastdouble(file)]);
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
