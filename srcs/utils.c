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

int	ft_isexportable(char *s)
{
	int	i;

	if (!((s[0] >= 'a' && s[0] <= 'z') || (s[0] >= 'A' && s[0] <= 'Z')
			|| s[0] == '_' || s[0] == '/'))
		return (0);
	i = -1;
	while (s[++i] && s[i] != '=')
		if (!((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] < 'Z') \
		|| (s[i] >= '0' && s[i] <= '9') || s[i] == '_'))
			return (0);
	return (1);
}
