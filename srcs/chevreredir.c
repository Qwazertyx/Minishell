#include "../incl/minishell.h"

char *doublechevre(char **file)
{

}

int	ft_chevreg(char **file)
{
	int		fd;
	int		i;
	char	*input;

	i = 0;
	while (file[i])
	{
		dprintf(2, "lllll%s\n", file[i]);
		if (file[i][0] != '<')
		{
			fd = open(&file[i][2], O_RDONLY);
			close(fd);
		}
		else if (file[i][0] == '<')
		{
			input = doublechevre(file);
		}
		i++;
	}
	fd = open(&file[i - 1][2], O_RDONLY);
	if (fd < 0)
		terminate();
	dup2(fd, STDIN_FILENO);
	return (0);
}
