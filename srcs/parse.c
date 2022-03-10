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

int	stop_while(char c, char *legal)
{
	int	i;

	i = -1;
	while (legal[++i])
		if (legal[i] == c)
			return (1);
	return (0);
}

char	*ft_dolar(char *a)
{
	int		i;
	char	*s;
	char	*gete;

	i = 0;
	while (a[i] && stop_while(a[i],
			"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01233456789_"))
		i++;
	s = malloc(i + 1);
	i = -1;
	while (a[++i] && stop_while(a[i],
			"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01233456789_"))
		s[i] = a[i];
	s[i] = '\0';
	gete = getenv(s);
	free(s);
	return (gete);
}

int	skip_dolar(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && stop_while(cmd[i],
			"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01233456789_"))
		i++;
	return (i);
}

char	*skip_quote(char *cmd, int n)
{
	char	*s;
	int		i;
	char	quot;

	quot = 0;
	i = 0;
	s = NULL;
	while (cmd[i])
	{
		if (quot == 0 && (cmd[i] == '\'' || cmd[i] == '\"'))
			quot = cmd[i];
		else if (quot != 0 && quot == cmd[i])
			quot = 0;
		if (cmd[i] == '$' && quot != '\'')
		{
			s = ft_joins(s, ft_dolar(&cmd[i + 1]));
			i += skip_dolar(&cmd[i + 1]);
		}
		else if (cmd[i] == '~' && quot == 0)
			s = ft_joins(s, getenv("HOME"));
		else if ((n == 1 || (quot != cmd[i] && quot != 0)
				|| (quot == 0 && cmd[i] != '\'' && cmd[i] != '\"')))
			s = ft_joinc(s, cmd[i]);
		i++;
	}
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
		p[i].cmd[0] = skip_quote(f_split(place_split(a, i)), 0);
		if (nb_param(place_split(a, i)) > 1)
			p[i].cmd[1] = skip_quote(l_split(place_split(a, i)), 1);
		p[i].cmd[nb_param(place_split(a, i))] = NULL;
		i++;
	}
	p[i].cmd = NULL;
	return (p);
}
