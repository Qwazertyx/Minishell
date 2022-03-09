#include "../incl/minishell.h"

int	nb_doublt(char *a)
{
	int		i;
	int		nb;
	char	quot;

	nb = 0;
	i = -1;
	quot = 0;
	while (a[++i])
	{
		if ((a[i] == '\'' || a[i] == '\"') && quot == 0)
			quot = a[i];
		else if ((a[i] == '\'' || a[i] == '\"') && quot != 0)
			quot = 0;
		if (a[i] == '|' && quot == 0)
			nb++;
	}
	return (nb + 1);
}

int	is_input(char *s)
{
	int		i;
	char	quot;

	i = 0;
	quot = 0;
	while (s[i])
	{
		if (quot == 0 && (s[i] == '\'' || s[i] == '\"'))
			quot = s[i];
		else if (quot == s[i])
			quot = 0;
		i++;
	}
	if (quot != 0)
	{
		printf("Missing %c quote\n", quot);
		return (0);
	}
	return (1);
}

int	nb_param(char *a)
{
	int	i;
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

char	*skip_quote(char *cmd)
{
	char	*s;
	int		i;
	int		nb;
	int		quot;

	quot = 0;
	i = 0;
	nb = 0;
	while(cmd[i])
	{
		if (cmd[i] == '\'' && quot == 0)
			quot = 1 + 0 * i++;
		else if (cmd[i] == '\"' && quot == 0)
			quot = 2 + 0 * i++;
		else if ((cmd[i] == '\"' && quot == 2) || (cmd[i] == '\'' && quot == 1))
			quot = 0 + 0 * i++;
		else if ((cmd[i] == '\"' && quot == 1) || (cmd[i] == '\'' && quot == 2)
			|| (cmd[i] != '\"' && cmd[i] != '\''))
			i = i + 1 + 0 * nb++;
	}
	s = malloc(nb + 1);
	i = 0;
	nb = 0;
	quot = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' && quot == 0)
			quot = 1 + 0 * i++;
		else if (cmd[i] == '\"' && quot == 0)
			quot = 2 + 0 * i++;
		else if ((cmd[i] == '\"' && quot == 2) || (cmd[i] == '\'' && quot == 1))
			quot = 0 + 0 * i++;
		else if ((cmd[i] == '\"' && quot == 1) || (cmd[i] == '\'' && quot == 2)
			|| (cmd[i] != '\"' && cmd[i] != '\''))
			s[nb++] = cmd[i++];
	}
	s[nb] = '\0';
	return (s);
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

t_var	*parse(char *a)
{
	t_var	*p;
	int		i;

	p = malloc(sizeof(t_var) * (nb_doublt(a) + 1));
	i = 0;
	while (i < nb_doublt(a))
	{
		p[i].cmd = malloc(sizeof(char *) * (nb_param(place_split(a, i)) + 1));
		p[i].cmd[0] = skip_quote(f_split(place_split(a, i)));
		if (nb_param(place_split(a, i)) > 1)
		{
			p[i].cmd[1] = l_split(place_split(a, i));
		}
		p[i].cmd[nb_param(place_split(a, i))] = NULL;
		p[i].output = NULL;
		i++;
	}
	p[i].cmd = NULL;
	p[i].output = NULL;
	return (p);
}
