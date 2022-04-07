#include "../incl/minishell.h"

int	ft_chevreg(char **file)
{
	int	fd;
	int	pipefd[2];
	int	i;

	dprintf(2, "lllll%s\n", &file[0][2]);
	i = 0;
	while (file[i])
	{
		fd = open(&file[i][2], O_RDONLY);
		close(fd);
		i++;
	}
	fd = open(&file[i - 1][2], O_RDONLY);
	if (fd < 0)
		terminate();
	dup2(fd, STDIN_FILENO);
	return (0);
}
