#include "../incl/minishell.h"

char	*no_chevre(char *s, char c)
{
	int		i;
	char	quot;
	char	*str;

	i = 0;
	quot = 0;
	str = NULL;
	while (s[i])
	{
		if (quot == 0 && (s[i] == '\'' || s[i] == '\"'))
			quot = s[i];
		else if (quot && quot == s[i])
			quot = 0;
		if (!quot && s[i] == c)
			i += skip_next_word(&s[i], c);
		str = ft_joinc(str, s[i]);
		if (!str)
			return (0);
		if (s[i])
			i++;
	}
	return (str);
}

char	*ft_nochevre(char *s, char c)
{
	char	*str;

	str = no_chevre(s, c);
	free(s);
	if (!str)
		return (0);
	return (str);
}

char	*filename(char *s)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = -1;
	while (s[i])
	{
		if (s[i] == '/')
			j = i;
		i++;
	}
	if (j == -1)
		return (0);
	str = malloc(j + 1);
	i = -1;
	while (++i < j)
		str[i] = s[i];
	str[i] = '\0';
	return (str);
}

int	end_chevre(char **file, int param)
{
	int		i;
	int		fd;
	int		f1;

	i = 0;
	while (file[i])
	{
		fd = open(&file[i][2], param, 0644);
		if (fd == -1)
		{
			ft_putstr_fd("Minishell: ", 2);
			perror(&file[i][2]);
			g_exit = 1;
			return (0);
		}
		i++;
		if (file[i])
			close(fd);
	}
	f1 = dup(1);
	dup2(fd, 1);
	return (f1);
}

int	ft_chevred(char **file)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	if (file[i][1] == '>')
	{
		if (file[i][0] == ' ')
		{
			ret = end_chevre(file, 1538);
			if (!ret)
				return (0);
		}
		else
		{
			ret = end_chevre(file, 522);
			if (!ret)
				return (0);
		}
	}
	return (ret);
}
