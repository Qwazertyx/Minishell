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
	if (a[i] && a[i] != '|')
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
	while (cmd && cmd[i])
	{
		if (quot == 0 && (cmd[i] == '\'' || cmd[i] == '\"'))
			quot = cmd[i];
		else if (quot != 0 && quot == cmd[i])
			quot = 0;
		if (cmd[i] == '$' && quot != '\'')
		{
			s = ft_joinsfree(s, ft_dolar(&cmd[i + 1], env));
			if (!s)
				return (NULL);
			i += skip_dolar(&cmd[i + 1]);
		}
		else if (cmd[i] == '~' && quot == 0)
		{
			s = ft_joins(s, ft_getenv("HOME", env));
			if (!s)
				return (NULL);
		}
		else if ((n == 1 || (quot != cmd[i] && quot != 0) \
		|| (quot == 0 && cmd[i] != '\'' && cmd[i] != '\"')) && (cmd[i] != ' ' \
		|| (i >= 1 && cmd[i] == ' ' && cmd[i - 1] && cmd[i - 1] != ' ')))
		{
			s = ft_joinc(s, cmd[i]);
			if (!s)
				return (NULL);
		}
		i++;
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
	dprintf(2, "\n\nICI\n(%s)\n======================\n", a);
	p->chevred[j] = NULL;
	p->chevreg[j] = NULL;
	free_split(pipe);
	return (a);
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

t_var	*ft_free_i(t_var *p, char *a, int i, int j)
{
	while (j >= 0)
		free(p->cmd[i + 1][j--]);
	free(p->cmd[i + 1]);
	while (i >= 0)
	{
		j = 1;
		while (j >= 0)
			free(p->cmd[i][j--]);
		free(p->cmd[i--]);
	}
	free(p->cmd);
	free_cmd(p->chevred);
	free_cmd(p->chevreg);
	free(a);
	ft_putstr_fd("parse error\n", 2);
	return (NULL);
}

int	ft_doublechevre(int *pipes[2], char ***file)
{
	int		i;
	int		j;
	char	*read;

	i = -1;
	while (file[++i])
	{
		j = -1;
		while (file[i][++j])
		{
			if (file[i][j][0] == '<')
			{
				read = readline("> ");
				while (ft_strcmp(read, &file[i][j][2]))
				{
					if (j == whoislastdouble(file[i]))
						ft_putendl_fd(read, pipes[1][i]);
					free(read);
					read = readline("> ");
				}
				free(read);
				close(pipes[1][i]);
				close(pipes[0][i]);
			}
		}
	}
	return (0);
}

int	*ft_heredoctest(t_var *p, char ***file)
{
	int		i;
	int		*pipes[2];
	int		pip[2];
	pid_t	pid;

	i = 0;
	while (file[i])
		i++;
	dprintf(2, "i ======= %d\n", i);
	pipes[0] = malloc((i + 1) * sizeof(int));
	pipes[1] = malloc((i + 1) * sizeof(int));
	i = -1;
	while (file[++i])
	{
		pipe(pip);
		pipes[0][i] = pip[0];
		pipes[1][i] = pip[1];
	}
	pipes[0][i] = 0;
	pipes[1][i] = 0;
	pid = fork();
	if (!pid)
	{
		signal(SIGINT, sig_heredoc);
		exit(ft_doublechevre(pipes, file));
	}
	else
	{
		i = -1;
		while (file[++i])
			close(pipes[1][i]);
		free(pipes[1]);
		return (pipes[0]);
	}
}

int	*ft_heredoc(t_var *p, char ***file)
{
	int	i;
	int	j;
	int	lastfd;
	int	*fd;

	i = 0;
	while (file[i])
		i++;
	fd = malloc((i + 1) * sizeof(int));
	if (!fd)
		return (0);
	i = -1;
	while (file[++i])
	{
		j = -1;
		lastfd = 0;
		fd[i] = 0;
		while (file[i][++j])
		{
			if (file[i][j][0] == '<')
				fd[i] = doublechevre(file[i], p, j);
			if (lastfd && fd[i] != lastfd)
				close(lastfd);
			lastfd = fd[i];
		}
	}
	return (fd);
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
	{
		p->cmd[i] = malloc((nb_param(place_split(a, i)) + 1) * sizeof(char *));
		printf("cmd = %p\n", p->cmd[i]);
		if (!p->cmd[i])
			return (ft_free_i(p, a, i - 1, -1));
		p->cmd[i][0] = skip_quote(f_split(place_split(a, i)), 0, *p->env);
		printf("p->cmd[%d] = %s\n", i, p->cmd[i][0]);
		if (!p->cmd[i][0])
			return (ft_free_i(p, a, i - 1, 0));
		if (nb_param(place_split(a, i)) > 1)
		{
			p->cmd[i][1] = skip_quote(l_split(place_split(a, i)), 1, *p->env);
			dprintf(2, "%p	%s\n", p->cmd[i][1], p->cmd[i][1]);
			if (!p->cmd[i][1])
				return (ft_free_i(p, a, i - 1, -1));
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
