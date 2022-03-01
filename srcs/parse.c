#include "../incl/minishell.h"

int	nb_split(char *a)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (a[i])
	{
		if (a[i +1] && a[i] == '|')
			nb++;
		i++;
	}
	return (nb + 1);
}

char	*f_split(char *a)
{
	int		i;
	char	*s;

	i = 0;
	while (a[i] && a[i] != ' ')
		i++;
	s = malloc(i + 1);
	i = 0;
	while (a[i] && a[i] != ' ')
	{
		s[i] = a[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*l_split(char *a)
{
	int		space;
	int		i;
	char	*s;

	space = 0;
	while (a[space] && a[space] != ' ')
		space++;
	i = space + 1;
	while (a[i] && a[i] != '|')
		i++;
	s = malloc(i + space + 1);
	i = space + 1;
	while (a[i] && a[i] != '|')
	{
		s[i - (space + 1)] = a[i];
		i++;
	}
	s[i - (space + 1)] = '\0';
	return (s);
}

char	*place_split(char *a, int nb)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (nb == 0)
		return (a);
	while (a[i])
	{
		if (a[i] == '|')
			n++;
		if (n == nb)
			return (&a[i + 2]);
		i++;
	}
	return (a);
}

char	**parse(char *a)
{
	char	**p;
	int		i;

	p = malloc(sizeof(char *) * 2 * nb_split(a));
	i = 0;
	while (i < 2 * nb_split(a))
	{
		p[i] = f_split(place_split(a, i / 2));
		i++;
		p[i] = l_split(place_split(a, i / 2));
		i++;
	}
	return (p);
}
