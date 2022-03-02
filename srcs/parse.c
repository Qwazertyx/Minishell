#include "../incl/minishell.h"

int	nb_split(char *a)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (a[i])
	{
		if (a[i] == ' ')
		{
			while (a[i] == ' ')
				i++;
			nb++;
		}
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
	if (i - space != 1)
		s = ft_strdup(&a[space + 1]);
	else
		s = ft_strdup(".");
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
	int		nb;

	nb = nb_split(a);
	p = malloc(sizeof(char *) * (nb + 1));
	// printf ("%d\n", nb);
	i = 0;
	while (i < nb)
	{
		p[i] = f_split(place_split(a, i / 2));
		i++;
		if (i < nb)
		{
			p[i] = l_split(place_split(a, i / 2));
			i++;
		}
	}
	p[i] = NULL;
	return (p);
}
