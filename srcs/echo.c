#include "../incl/minishell.h"

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	*get_sus(char *cmd, char **envp, char *toech, int j)
{
	char	*sus;
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
	else
	{
		write(1, "$", 1);
		ft_putstr_fd(toech, 1);
	}
	return (0);
}

int	echospecial(char *cmd, char **envp, int i)
{
	int		j;
	char	*toech;

	j = 0;
	while (cmd[i + j] && cmd[i + j] != ' ')
		j++;
	toech = malloc((j + 1) * sizeof(char));
	j = 0;
	while (cmd[i + j] && cmd[i + j] != ' ')
	{
		toech[j] = cmd[i + j];
		j++;
	}
	toech[j] = 0;
	get_sus(cmd, envp, toech, j);
	return (j);
}

int	nparam(char *cmd)
{
	if (cmd[0] && cmd[1] && cmd[2]
		&& cmd[0] == '-' && cmd[1] == 'n' && cmd[2] == ' ')
		return (3);
	return (0);
}

int	echomaster(char *cmd, char **envp)
{
	int	i;
	int	quot;

	i = nparam(cmd);
	quot = 0;
	while (cmd[i])
	{
		if (cmd[i] == '$')
			i += echospecial(cmd, envp, i + 1);
		//else if (cmd[i + 1] && cmd[i] == ' ' && cmd[i + 1] == ' ' && quot == 0)
		//	i++;
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
	if (!nparam(cmd))
		write(1, "\n", 1);
	return (1);
}
