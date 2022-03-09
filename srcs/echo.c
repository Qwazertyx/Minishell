#include "../incl/minishell.h"

int	*get_sus(char **envp, char *toech, int j, char **s)
{
	int		i;
	int		p;

	i = 0;
	p = 0;
	while (envp[i] && !ft_strnstr(envp[i], toech, j))
		i++;
	if (envp[i] && envp[i][j] == '=')
	{
		while (p < j + 1)
			p++;
		*s = ft_joins(*s, &envp[i][p]);
		// printf("%s || %s\n", s, &envp[i][p]);
		// while (envp[i][p])
		// {
		// 	ft_putchar(envp[i][p]);
		// 	s = ft_joinc(s, envp[i][p++]);
		// }
	}
	return (0);
}

int	echospecial(char *cmd, char **envp, int i, char **s)
{
	int		j;
	char	*toech;

	j = 0;
	while (cmd[i + j] && (cmd[i + j] != ' '
			&& cmd[i + j] != '\'' && cmd[i + j] != '\"'))
		j++;
	toech = malloc((j + 1) * sizeof(char));
	j = 0;
	while (cmd[i + j] && (cmd[i + j] != ' '
			&& cmd[i + j] != '\'' && cmd[i + j] != '\"'))
	{
		toech[j] = cmd[i + j];
		j++;
	}
	toech[j] = 0;
	if (cmd[i + j] && cmd[i + j] == '\'')
	{
		*s = ft_joinc(*s, '$');
		*s = ft_joins(*s, toech);
	}
	else
		get_sus(envp, toech, j, s);
	return (j);
}

int	nparam(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] == ' ')
		i++;
	if (cmd[i] && cmd[i] == '-')
	{
		i++;
		if (cmd[i] && cmd[i] == 'n')
		{
			while (cmd[i] && cmd[i] == 'n')
				i++;
			if (cmd[i] && cmd[i] == ' ')
				return (i);
		}
	}
	return (0);
}

char	*echoservant(char *cmd, char **envp, int i)
{
	int		quot;
	char	*s;

	quot = 0;
	s = NULL;
	while (cmd[i])
	{
		if (cmd[i] == '$')
			i += echospecial(cmd, envp, i + 1, &s);
		else if (cmd[i - 1] && cmd[i] == ' ' && cmd[i - 1] == ' ' && quot == 0)
			i++;
		else if (cmd[i] == '\'' && quot == 0)
			quot = 1;
		else if (cmd[i] == '\"' && quot == 0)
			quot = 2;
		else if ((cmd[i] == '\"' && quot == 2) || (cmd[i] == '\'' && quot == 1))
			quot = 0;
		else if ((cmd[i] == '\"' && quot == 1) || (cmd[i] == '\'' && quot == 2)
			|| ((cmd[i] != '\"' && cmd[i] != '\'')))
			s = ft_joinc(s, cmd[i]);
		i++;
	}
	return (s);
}

char	*echomaster(char *cmd, char **envp)
{
	int		i;
	int		quot;
	char	*s;

	s = NULL;
	i = 0;
	while (cmd[i] == ' ')
		i++;
	i = nparam(cmd);
	while (cmd[i] == ' ')
		i++;
	quot = 0;
	s = echoservant(cmd, envp, i);
	if (!nparam(cmd))
		ft_joinc(s, '\n');
	return (s);
}
