#include "../incl/minishell.h"

int	*get_sus(char **envp, char *toech, int j)
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
		while (envp[i][p])
			ft_putchar(envp[i][p++]);
	}
	return (0);
}

int	echospecial(char *cmd, char **envp, int i)
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
		write(1, "$", 1);
		ft_putstr_fd(toech, 1);
	}
	else
		get_sus(envp, toech, j);
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

int	echoservant(char *cmd, int i)
{
	int	quot;

	quot = 0;
	while (cmd[i])
	{
		if (i != 0 && cmd[i - 1] && cmd[i] == ' ' && cmd[i - 1] == ' ' && quot == 0)
			i++;
		else if (!cmd[i + 1] && cmd[i] == ' ' && quot == 0)
			i++;
		else if (cmd[i] == '\'' && quot == 0)
			quot = 1;
		else if (cmd[i] == '\"' && quot == 0)
			quot = 2;
		else if ((cmd[i] == '\"' && quot == 2) || (cmd[i] == '\'' && quot == 1))
			quot = 0;
		else if ((cmd[i] == '\"' && quot == 1) || (cmd[i] == '\'' && quot == 2)
			|| ((cmd[i] != '\"' && cmd[i] != '\'')))
			ft_putchar(cmd[i]);
		i++;
	}
	return (1);
}

int	echomaster(char *cmd)
{
	int	i;
	int	quot;

	i = 0;
	if (!cmd)
		return (0);
	while (cmd[i] == ' ')
		i++;
	i = nparam(cmd);
	while (cmd[i] == ' ')
		i++;
	quot = 0;
	echoservant(cmd, i);
	if (!nparam(cmd))
		write(1, "\n", 1);
	return (1);
}
