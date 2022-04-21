#include "../incl/minishell.h"

char	*while_ft_nochevre(char *s, char c, char *str)
{
	int		i;
	char	quot;

	i = 0;
	quot = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			i++;
			if (s[i] == c)
				i++;
			while (s[i] && s[i] == ' ')
				i++;
			while (s[i] && (s[i] != ' ' || quot != 0))
			{
				if (quot == 0 && (s[i] == '\'' || s[i] == '\"'))
					quot = s[i];
				else if (quot && quot == s[i])
					quot = 0;
				i++;
			}
		}
		if (s[i])
			str = ft_joinc(str, s[i++]);
	}
	return (str);
}

char	*ft_nochevre(char *s, char c)
{
	char	*str;

	str = while_ft_nochevre(s, c, NULL);
	free(s);
	if (!str)
		return (0);
	return (str);
}

void	end_chevre(char **file, int param)
{
	int	i;
	int	fd;

	i = 0;
	while (file[i])
	{
		if (access(&file[i][2], F_OK | W_OK) == -1)
		{
			ft_putstr_fd("Minishell: ", 2);
			ft_putstr_fd(&file[i][2], 2);
			if (access(&file[i][2], F_OK) == -1)
				ft_putstr_fd(": No such file or directory\n", 2);
			else if (access(&file[i][2], W_OK) == -1)
				ft_putstr_fd(": Permission denied\n", 2);
			exit (1);
		}
		fd = open(&file[i][2], param, 0777);
		close(fd);
		i++;
	}
	fd = open(&file[i - 1][2], param);
	dup2(fd, 1);
}

int	ft_chevred(char **file)
{
	int		i;

	i = 0;
	if (file[i][1] == '>')
	{
		if (file[i][0] == ' ')
			end_chevre(file, 1538);
		else
			end_chevre(file, 522);
	}
	return (0);
}
