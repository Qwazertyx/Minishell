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

int	ft_strchrquot(char *s, char c, char c2)
{
	int		i;
	char	quot;

	i = 0;
	quot = 0;
	while (s && s[i])
	{
		if (quot == 0 && (s[i] == '\'' || s[i] == '\"'))
			quot = s[i];
		else if (s[i] == quot)
			quot = 0;
		if (quot == 0 && s[i] == c && (c2 == 0 || (s[i + 1] && s[i + 1] == c2)))
			return (i + 1);
		i++;
	}
	return (-1);
}

int	ft_strchr(char *a, char c)
{
	int	i;

	i = 0;
	while (a[i] && a[i] != c)
		i++;
	if (a[i] && a[i] == c)
		return (i);
	return (-1);
}

void	ft_normal_fd(t_var *p, int fd[2], int i)
{
	wait(NULL);
	if (!has_a_single(p->chevreg[i]))
		dup2(fd[0], 0);
	if (p->chevred[i][0])
		dup2(fd[1], 1);
}

char	*ft_strdup(char *a)
{
	int		i;
	char	*s;

	i = 0;
	if (!a)
		return (0);
	while (a[i])
		i++;
	s = malloc(i + 1);
	i = -1;
	while (a[++i])
		s[i] = a[i];
	s[i] = '\0';
	return (s);
}

pid_t	ft_strcmp(char *a, char *b)
{
	int	i;

	i = 0;
	if (!a || !b)
		return (0);
	while (a[i] && b[i] && a[i] == b[i])
		i++;
	return (a[i] - b[i]);
}

char	*ft_strndup(char *a, int l)
{
	int		i;
	char	*s;

	i = 0;
	s = malloc(l + 1);
	while (a[i] && i < l)
	{
		s[i] = a[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}
