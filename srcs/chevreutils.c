#include "../incl/minishell.h"

int	skip_next_word(char *s, char c)
{
	int		i;
	char	quot;

	// dprintf(450, "s = %s\n", s);
	i = 1;
	quot = 0;
	if (s[i] == c)
		i++;
	// dprintf(450, "i2 = %d\n", i);
	while (s[i] && s[i] == ' ')
		i++;
	// dprintf(450, "i2 = %d\n", i);
	while (s[i])
	{
		if (quot == 0 && (s[i] == '\'' || s[i] == '\"'))
			quot = s[i];
		else if (quot && quot == s[i])
			quot = 0;
		if (!quot && (s[i] == ' ' || s[i] == '|'))
			return (i);
		i++;
	}
	return (i);
}

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

	str = no_chevre(s, c);
	// str = while_ft_nochevre(s, c, NULL);
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

void	end_chevre(char **file, int param)
{
	int		i;
	int		fd;
	char	*fname;

	i = 0;
	while (file[i])
	{
		fd = open(&file[i][2], param, 0777);
		if (fd == -1)
		{
			ft_putstr_fd("Minishell: ", 2);
			perror(&file[i][2]);
			exit(1);
		}
		i++;
		if (file[i])
			close(fd);
	}
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
