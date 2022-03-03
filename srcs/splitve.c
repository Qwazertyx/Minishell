#include "../incl/minishell.h"

static int	ft_nb_w(const char *s, char c)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (s && s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != '\0')
			nb++;
		while (s[i] != c && s[i])
			i++;
	}
	return (nb);
}

static char	*ft_strncpy(char *dest, const char *str, int n)
{
	int	i;

	i = -1;
	while (str && str[++i] && i < n)
		dest[i] = str[i];
	dest[i] = '\0';
	return (dest);
}

static char	*mallocdef(char **tab, int j, int len)
{
	tab[j] = malloc(len);
	if (!tab[j])
	{
		while (-j > 0)
			free(tab[j]);
		free(tab);
		return (0);
	}
	return (tab[j]);
}

static int	ft_skip(char *s, char c, int i)
{
	char	quot;

	quot = 0;
	while (s && s[i] && s[i] != c)
	{
		if (s[i] == '\'' && quot == 0)
			quot = '\'';
		else if (s[i] == '\"' && quot == 0)
			quot = '\"';
		if (quot)
			while (s[i] != quot)
				i++;
		if (s[i] == quot)
			quot = 0;
		i++;
	}
	return (i);
}

char	**ft_splitve(char *arg, char c, char *cmd)
{
	int		i;
	int		j;
	int		l;
	char	**tab;

	tab = malloc(sizeof(char *) * (ft_nb_w(arg, c) + 2));
	if (!tab)
		return (0);
	tab[0] = ft_strdup(cmd);
	i = 0;
	j = 1;
	while (j < ft_nb_w(arg, c) + 1)
	{
		while (arg && arg[i] == c && arg[i])
			i++;
		l = i;
		i = ft_skip(arg, c, i);
		tab[j] = mallocdef(tab, j, i - l + 1);
		if (!tab[j])
			return (0);
		tab[j] = ft_strncpy(tab[j], &arg[l], i - l);
		j++;
	}
	tab[j] = 0;
	return (tab);
}
