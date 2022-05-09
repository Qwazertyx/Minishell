#include "../incl/minishell.h"

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
		{
			i++;
			while (a[i] && a[i] == ' ')
				i++;
			return (&a[i]);
		}
		i++;
	}
	return (a);
}

char	*ft_no_doublespace(char *s)
{
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	while (s[i])
	{
		if (s[i] == ' ')
		{
			while (s[i] && s[i] == ' ')
				i++;
			if (!s[i])
				return (str);
			str = ft_joinc(str, ' ');
			if (!str)
				return (0);
		}
		str = ft_joinc(str, s[i]);
		if (!str)
			return (0);
		i++;
	}
	return (str);
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
	p->chevred = malloc((i + 1) * sizeof(char **));
	p->chevreg = malloc((i + 1) * sizeof(char **));
	j = 0;
	while (j < i)
	{
		p->chevred[j] = ft_sfilechevre(pipe[j], '>');
		p->chevreg[j] = ft_sfilechevre(pipe[j], '<');
		j++;
	}
	temp = ft_nochevre(ft_nochevre(a, '>'), '<');
	a = ft_no_doublespace(temp);
	free(temp);
	p->chevred[j] = NULL;
	p->chevreg[j] = NULL;
	free_split(pipe);
	return (a);
}

int	ft_fill_cmd(char *a, t_var *p, int i)
{
	p->cmd[i] = malloc((nb_param(place_split(a, i)) + 1) * sizeof(char *));
	if (!p->cmd[i])
		return (ft_free_i(p, a, i - 1, -1));
	p->cmd[i][0] = skip_quote(f_split(place_split(a, i)), 0, *p->env, NULL);
	if (!p->cmd[i][0])
		return (ft_free_i(p, a, i - 1, 0));
	if (nb_param(place_split(a, i)) > 1)
	{
		p->cmd[i][1] = skip_quote(l_split(place_split(a, i)), 1, *p->env, NULL);
		if (!p->cmd[i][1])
			return (ft_free_i(p, a, i - 1, -1));
		p->cmd[i][2] = NULL;
	}
	else
		p->cmd[i][1] = NULL;
	return (1);
}

t_var	*parse(char *a, t_var *p)
{
	int		i;

	a = ft_parsechevre(a, p);
	if (!a)
	{
		ft_putstr_fd("parse error \n", 2);
		return (0);
	}
	if (!ft_verifchevre(p))
		return (free_returned(p, a));
	p->cmd = malloc((nb_doublt(a) + 1) * sizeof(char **));
	i = 0;
	while (i < nb_doublt(a))
		if (!ft_fill_cmd(a, p, i++))
			return (0);
	p->cmd[i] = NULL;
	free(a);
	return (p);
}
