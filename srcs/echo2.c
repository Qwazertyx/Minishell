#include "../incl/minishell.h"

int	echospecial(char *cmd, char **envp, int i)
{
	int		j;
	char	*toech;

	j = 0;
	while (cmd[i + j] != ' ')
		j++;
	toech = malloc((j + 1) * sizeof(char));
	toech[0] = cmd[i];
	j = 0;
	while (cmd[i + j] != ' ')
	{
		toech[j] = cmd[i + j];
		j++;
	}
	toech[j] == 0;
	printf("|%s|", toech);
	return (j);
}

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	echomaster(char *cmd, char **envp)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] && cmd[i] == '\'')
			while (cmd[i] && cmd[i] != '\'')
				ft_putchar(cmd[i++]);
		else if (cmd[i] && cmd[i] == '\"')
		{
			while (cmd[i] && cmd[i] != '\"')
			{
				ft_putchar(cmd[i++]);
			}
		}
		else if (cmd[i])
			ft_putchar(cmd[i]);
	}
	return (1);
}
