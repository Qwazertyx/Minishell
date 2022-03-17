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

int	contains(char *a, char c)
{
	int	i;

	i = 0;
	while (a[i])
		if (a[i++] == c)
			return (1);
	return (0);
}
