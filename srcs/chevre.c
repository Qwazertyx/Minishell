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

char	*ft_chevrecpy(char *ch, char c)
{
	int		i;
	int		sp;
	char	*s;

	sp = 0;
	while (ch[sp] && ch[sp] == ' ')
		sp++;
	i = sp;
	while (ch[i] && ch[i] != ' ' && ch[i] != c)
		i++;
	s = malloc(i - sp + 1);
	i = sp - 1;
	while (ch[++i] && ch[i] != ' ' && ch[i] != c)
	{
		s[i - sp] = ch[i];
	}
	s[i - sp] = '\0';
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
			file[j++] = ft_chevrecpy(&ch[oldi], c);
		printf("--%s\n", file[j - 1]);
	}
	file[j] = NULL;
	return (file);
}

char	*ft_nochevre(char *s, char c)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			while (s[i] && s[i] == ' ')
				i++;
			while (s[i] && s[i] != ' ')
				i++;
		}
		i = i + 1 + 0 * len++;
	}
	str = malloc(len + 1);
	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			while (s[i] && s[i] == ' ')
				i++;
			while (s[i] && s[i] != ' ')
				i++;
		}
		str[len++] = s[i++];
	}
	str[len] = '\0';
	return (str);
}

int	s_chevred(char *ch)
{
	int		i;
	int		fd;
	int		returned;
	char	**file;

	file = ft_sfilechevre(ch, '>');
	i = 0;
	while (file[i])
	{
		fd = open(file[i], O_RDWR | O_TRUNC | O_CREAT, 0777);
		close(fd);
		i++;
	}
	fd = open(file[i - 1], O_RDWR);
	returned = dup(1);
	dup2(fd, 1);
	return (returned);
}
