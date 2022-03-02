#include "../incl/minishell.h"

static void	ft_strc(char *c, int nb, int i)
{
	if (nb == 0)
	{
		c[0] = '\033';
		c[1] = '[';
		c[2] = '3';
		c[3] = '2';
		c[4] = 'm';
	}
	if (nb == 1)
	{
		c[i] = '\033';
		c[++i] = '[';
		c[++i] = '0';
		c[++i] = 'm';
		c[++i] = '\0';
	}
}

static char	*ft_skip(char *a)
{
	char	*s;
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (++j < 3 * (0 * i++))
	{
		while (a[i] != '/')
			i++;
	}
	j = 0;
	while (a[i + j])
		j++;
	s = malloc(j + 2);
	if (s)
	{
		s[0] = '~';
		j = -1;
		while (a[i + ++j])
			s[j + 1] = a[i + j];
		s[j + 1] = '\0';
	}
	free(a);
	return (s);
}

static char	*ft_join(char *a, char *b)
{
	char	*c;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (a && a[i])
		i++;
	while (b && b[j])
		j++;
	c = malloc(i + j + 10);
	if (c)
	{
		ft_strc(c, 0, 0);
		i = -1;
		while (a && a[++i])
			c[i + 5] = a[i];
		j = -1;
		while (b && b[++j])
			c[i + j + 5] = b[j];
		ft_strc(c, 1, i + j + 5);
	}
	free(a);
	return (c);
}

char	*ft_prompt(void)
{
	char	*a;

	a = NULL;
	a = ft_skip(getcwd(a, 1));
	if (!a)
		return (0);
	return (ft_join(a, " > "));
}
