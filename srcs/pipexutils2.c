#include "../incl/minishell.h"

int	ft_conststrlen(char const *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	nbwords(const char *str, char c)
{
	int	i;
	int	isword;

	i = 0;
	isword = 0;
	while (*str)
	{
		if (*str != c && isword == 0)
		{
			isword = 1;
			i++;
		}
		else if (*str == c)
			isword = 0;
		str++;
	}
	return (i);
}

char	*getword(char const *s, int start, int stop)
{
	char	*split;
	int		i;

	i = 0;
	split = malloc((stop - start + 1) * sizeof(char));
	while (start < stop)
		split[i++] = s[start++];
	split[i] = 0;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		start;
	char	**split;

	if (!s)
		return (0);
	split = malloc((nbwords(s, c) + 1) * sizeof(char *));
	if (!split)
		return (0);
	i = -1;
	j = 0;
	start = -1;
	while (++i <= ft_conststrlen(s))
	{
		if (s[i] != c && start < 0)
			start = i;
		else if ((s[i] == c || i == ft_conststrlen(s)) && start >= 0)
		{
			split[j++] = getword(s, start, i);
			start = -1;
		}
	}
	split[j] = 0;
	return (split);
}
