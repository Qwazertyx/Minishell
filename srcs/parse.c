#include "../incl/minishell.h"

int	nb_doublt(char *a)
{
	int	i;
	int	nb;

	nb = 0;
	i = -1;
	while (a[++i])
		if (a[i] == '|')
			nb++;
	return (nb + 1);
}

int	nb_param(char *a)
{
	int i;
	int	nb;

	i = 0;
	nb = 1;
	while (a[i] && a[i] != ' ')
		i++;
	while (a[i] && a[i] == ' ')
		i++;
	if (a[i])
		nb++;
	return (nb);
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
	s = ft_strndup(&a[space + 1], i - space - 1);
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

char	***parse(char *a)
{
	char	***p;
	int		i;
	int		nb;

	p = malloc(sizeof(char **) * (nb_doublt(a) + 1));
	i = 0;
	while (i < nb_doublt(a))
	{
		p[i] = malloc(sizeof(char *) * (nb_param(place_split(a, i)) + 1));
		p[i][0] = f_split(place_split(a, i));
		if (nb_param(place_split(a , i)) > 1)
		{
			p[i][1] = l_split(place_split(a, i));
		}
		p[i][nb_param(place_split(a , i))] = NULL;
		i++;
	}
	p[i] = NULL;
	return (p);
}
