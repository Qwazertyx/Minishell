#include "../incl/minishell.h"

int	nb_schevre(char *ch, char c)
{
	int	nb;
	int	i;
	int	oldi;

	i = ft_strchrquot(ch, c, 0);
	nb = 0;
	if (i != -1 && ch[i] && ch[i] != c)
		nb++;
	oldi = i;
	while (i != -1)
	{
		i = ft_strchrquot(&ch[oldi], c, 0);
		oldi += i;
		if (i != -1 && ch[oldi] != c)
			nb++;
	}
	return (nb);
}

char	*ft_chevrecpy(char *ch, char c1, char c2)
{
	int		i;
	int		sp;
	char	*s;

	sp = 0;
	while (ch[sp] && ch[sp] == ' ')
		sp++;
	i = sp;
	while (ch[i] && ch[i] != ' ' && ch[i] != '>' && ch[i] != '<')
		i++;
	s = malloc(i - sp + 3);
	s[0] = c1;
	s[1] = c2;
	i = sp - 1;
	while (ch[++i] && ch[i] != ' ' && ch[i] != '>' && ch[i] != '<')
		s[(i - sp) + 2] = ch[i];
	s[(i - sp) + 2] = '\0';
	return (s);
}

char	**ft_sfilechevre(char *ch, char c)
{
	char	**file;
	int		i;
	int		oldi;
	int		j;

	file = malloc(sizeof(char *) * (nb_schevre(ch, c) + 1));
	j = 0;
	oldi = 0;
	while (j < nb_schevre(ch, c))
	{
		i = ft_strchrquot(&ch[oldi], c, 0);
		oldi += i;
		if (ch[oldi] != c)
		{
			if (ch[oldi - 2] && ch[oldi - 2] == ch[oldi - 1])
				file[j++] = ft_chevrecpy(&ch[oldi], ch[oldi - 2], ch[oldi - 1]);
			else
				file[j++] = ft_chevrecpy(&ch[oldi], ' ', ch[oldi - 1]);
		}
		// printf("file = (%s)\n", file[j - 1]);
	}
	file[j] = NULL;
	return (file);
}

char	*no_endspace(char *s)
{
	int		i;
	char	*str;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	i--;
	while (i > 0 && s[i] == ' ')
		i--;
	str = ft_strndup(s, i + 1);
	free(s);
	return (str);
}

char	*ft_nochevre(char *s, char c)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = 0;
	while (s[i] && s[i] == ' ')
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			i++;
			while (s[i] && s[i] == ' ')
				i++;
			while (s[i] && s[i] != ' ')
				i++;
		}
		if (s[i])
			i = i + 1 + 0 * len++;
	}
	str = malloc(len + 1);
	i = 0;
	len = 0;
	while (s[i] && s[i] == ' ')
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			i++;
			while (s[i] && s[i] == ' ')
				i++;
			while (s[i] && s[i] != ' ')
				i++;
		}
		if (s[i])
			str[len++] = s[i++];
	}
	str[len] = '\0';
	free(s);
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
			fd = end_chevre(file, 1538);
		else
			fd = end_chevre(file, 522);
	}
	else
	{
		if (file[i][0] == ' ');
		else ;
	}
	return (fd);
}