#include "../incl/minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	c;

	c = 0;
	if (s)
	{
		while (s[c])
			c++;
			write(fd, s, c);
	}
}

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}
