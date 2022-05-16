#include "../incl/minishell.h"

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
	if (a[i] && a[i] != '|')
		nb++;
	return (nb);
}

char	*special_joinsfree_skip(char *a, char **b, char *s, int *i)
{
	s = ft_joinsfree(s, ft_dolar(a, b));
	if (!s)
		return (0);
	*i += skip_dolar(a);
	return (s);
}

char	*skip_quote(char *cmd, int n, char **env, char *s)
{
	int		i;
	char	quot;

	quot = 0;
	i = -1;
	while (cmd && cmd[++i])
	{
		if (quot == 0 && (cmd[i] == '\'' || cmd[i] == '\"'))
			quot = cmd[i];
		else if (quot != 0 && quot == cmd[i])
			quot = 0;
		if (cmd[i] == '$' && quot != '\'')
			s = special_joinsfree_skip(&cmd[i + 1], env, s, &i);
		else if (cmd[i] == '~' && (!cmd[i + 1] || cmd[i + 1] == ' ') \
		&& (i == 0 || (i > 0 && cmd[i - 1] == ' ')) && quot == 0)
			s = ft_joins(s, ft_getenv("HOME", env));
		else if ((n == 1 || (quot != cmd[i] && quot != 0) \
		|| (quot == 0 && cmd[i] != '\'' && cmd[i] != '\"')) && (cmd[i] != ' ' \
		|| (i >= 1 && cmd[i] == ' ' && cmd[i - 1] && cmd[i - 1] != ' ')))
			s = ft_joinc(s, cmd[i]);
		if (!s)
			return (0);
	}
	free(cmd);
	return (s);
}

char	*f_split(char *a)
{
	int		i;
	char	*s;
	char	quot;

	i = 0;
	quot = 0;
	s = NULL;
	i = 0;
	while (a[i] && (quot || a[i] != ' ') && (quot || a[i] != '|'))
	{
		if (quot == 0 && (a[i] == '\'' || a[i] == '\"'))
			quot = a[i];
		else if (quot && quot == a[i])
			quot = 0;
		s = ft_joinc(s, a[i]);
		if (!s)
			return (0);
		i++;
	}
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
