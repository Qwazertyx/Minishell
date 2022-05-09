#include "../incl/minishell.h"

int	nb_schevre(char *ch, char c)
{
	int	nb;
	int	i;
	int	oldi;

	i = ft_strchrquot(ch, c, 0);
	nb = 0;
	if (i != -1)
		nb++;
	if (i >= 0 && ch[i] && ch[i] == c)
		nb--;
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
	char	quot;

	sp = 0;
	while (ch[sp] && ch[sp] == ' ')
		sp++;
	i = sp;
	s = malloc(3);
	s[0] = c1;
	s[1] = c2;
	s[2] = '\0';
	quot = 0;
	while (ch[i] && ((ch[i] != ' ' && ch[i] != '>' && ch[i] != '<') || quot))
	{
		if (!quot && (ch[i] == '\'' || ch[i] == '\"'))
			quot = ch[i++];
		else if (quot && quot == ch[i])
			quot = 0 * i++;
		if (ch[i])
			s = ft_joinc(s, ch[i++]);
	}
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
