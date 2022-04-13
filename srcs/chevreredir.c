#include "../incl/minishell.h"

char	*doublechevre(char **file, t_var *tab, int i)
{
	int		y;
	char	*heredoc;
	char	*stop;
	char	*read;

	y = 0;
	stop = malloc(ft_strlen(file[i]) - 2 + 1);
	while (file[i][y + 2])
	{
		stop[y] = file[i][y + 2];
		y++;
	}
	stop[y] = 0;
	read = readline(0);
	while (!ft_strnstr(read, stop, ft_strlen(read)))
	{
		read = readline(0);
	}
	dprintf(2, "sortie sortie sortie\n");
	return (read);
}

int	ft_chevreg(char **file, t_var *tab)
{
	int		i;
	int		fd;

	i = 0;
	while (file[i])
	{
		if (file[i][0] != '<')
		{
			dprintf(2, "sheeesh : %s\n", file[i]);
			fd = open(&file[i][2], O_RDONLY);
			close(fd);
		}
		else if (file[i][0] == '<')
		{
			dprintf(2, "double sheeesh : %s\n", file[i]);
			doublechevre(file, tab, i);
		}
		i++;
	}
	if (file[i - 1][2] != '<')
	{
		fd = open(&file[i - 1][2], O_RDONLY);
		if (fd < 0)
			terminate();
		dup2(fd, STDIN_FILENO);
	}
	else
	{
		doublechevre(file, tab, i);
		dup2(STDOUT_FILENO, STDIN_FILENO);
	}
	return (0);
}
