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

int	end_chevre(char **file, int param)
{
	int	i;
	int	fd;
	int	returned;

	i = 0;
	while (file[i])
	{
		fd = open(&file[i][2], param, 0777);
		close(fd);
		i++;
	}
	fd = open(&file[i - 1][2], param);
	returned = dup(1);
	dup2(fd, 1);
	return (returned);
}

int	ft_chevred(char **file)
{
	int		i;
	int		fd;

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
