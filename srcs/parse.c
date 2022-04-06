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
		ft_putstr_fd("Missing ", 2);
		write(2, &quot, 1);
		ft_putstr_fd(" quote\n", 2);
		free(s);
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

char	*ft_dolar(char *a, char **env)
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
	gete = ft_strdup(ft_getenv(s, env));
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

char	*skip_quote(char *cmd, int n, char **env)
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
			s = ft_joinsfree(s, ft_dolar(&cmd[i + 1], env));
			i += skip_dolar(&cmd[i + 1]);
		}
		else if (cmd[i] == '~' && quot == 0)
			s = ft_joins(s, ft_getenv("HOME", env));
		else if ((n == 1 || (quot != cmd[i] && quot != 0)
				|| (quot == 0 && cmd[i] != '\'' && cmd[i] != '\"'))
				&& (cmd[i] != ' ' || (i >= 1 && cmd[i] == ' ' && cmd[i - 1] && cmd[i - 1] != ' ')))
			s = ft_joinc(s, cmd[i]);
		i++;
	}
	free(cmd);
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

char	*ft_parsechevre(char *a, t_var *p)
{
	char	**pipe;
	char	*temp;
	int		i;
	int		j;

	pipe = ft_split(a, '|');
	i = 0;
	while (pipe[i])
		i++;
	p->chevred = malloc(sizeof(char **) * (i + 1));
	p->chevreg = malloc(sizeof(char **) * (i + 1));
	printf("%d\n", i);
	j = 0;
	while (j < i)
	{
		p->chevred[j] = ft_sfilechevre(pipe[j], '>');
		dprintf(2, "%s\n", p->chevred[j][0]);
		p->chevreg[j] = ft_sfilechevre(pipe[j], '<');
		dprintf(2, "%s\n", p->chevreg[j][0]);
		j++;
	}
	temp = ft_nochevre(a, '>');
	a = ft_nochevre(temp, '<');
	p->chevred[j] = NULL;
	p->chevreg[j] = NULL;
	free_split(pipe);
	return (a);
}

int	check_exist(char *s)
{
	int		i;
	char	*path;
	int		returned;

	i = 2;
	while (s[i] && s[i] != '/')
		i++;
	path = malloc(i - 1);
	i = 1;
	while (s[++i] && s[i] != '/')
		path[i - 2] = s[i];
	path[i - 2] = '\0';
	returned = access(path, F_OK | W_OK);
	free(path);
	return (returned);
}

int	ft_verifchevred(t_var *p)
{
	int		i;
	int		j;

	i = -1;
	while (p->chevred[++i])
	{
		j = -1;
		while (p->chevred[i][++j])
		{
			if (!p->chevred[i][j][2])
				return (0);
			if (ft_strchrquot(p->chevred[i][j], '/', 0) != -1)
				if (check_exist(p->chevred[i][j]) == -1)
					return (0);
		}
	}
	return (1);
}

int	ft_verifchevreg(t_var *p)
{
	int		i;
	int		j;

	i = -1;
	while (p->chevreg[++i])
	{
		j = -1;
		while (p->chevreg[i][++j])
		{
			if (!p->chevreg[i][j][2])
				return (0);
			if (ft_strchrquot(p->chevreg[i][j], '/', 0) != -1)
				if (check_exist(p->chevreg[i][j]) == -1)
					return (0);
		}
	}
	return (1);
}

t_var	*free_returned(t_var *p, char *a)
{
	free(a);
	free_cmd(p->chevred);
	free_cmd(p->chevreg);
	return (NULL);
}

int	ft_verifchevre(t_var *p)
{
	if (!ft_verifchevred(p) || !ft_verifchevreg(p))
	{
		ft_putstr_fd("Minishell: syntax error\n", 2);
		return (0);
	}
	return (1);
}

t_var	*parse(char *a, t_var *p)
{
	int		i;

	a = ft_parsechevre(a, p);
	if (!ft_verifchevre(p))
		return (free_returned(p, a));
	p->cmd = malloc(sizeof(char **) * (nb_doublt(a) + 1));
	i = 0;
	while (i < nb_doublt(a))
	{
		p->cmd[i] = malloc(sizeof(char *) * (nb_param(place_split(a, i)) + 1));
		p->cmd[i][0] = skip_quote(f_split(place_split(a, i)), 0, *p->env);
		if (nb_param(place_split(a, i)) > 1)
		{
			p->cmd[i][1] = skip_quote(l_split(place_split(a, i)), 1, *p->env);
			p->cmd[i][2] = NULL;
		}
		else
			p->cmd[i][1] = NULL;
		i++;
	}
	p->cmd[i] = NULL;
	free(a);
	return (p);
}
