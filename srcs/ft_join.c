#include "../incl/minishell.h"

char	*ft_joinc(char *s1, char c)
{
	int		i;
	char	*s;

	i = 0;
	while (s1 && s1[i])
		i++;
	s = malloc(i + 2);
	if (s)
	{
		i = -1;
		while (s1 && s1[++i])
			s[i] = s1[i];
		if (i == -1)
			i = 0;
		s[i] = c;
		s[i + 1] = '\0';
	}
	free(s1);
	return (s);
}

char	*ft_joins(char *a, char *b)
{
	int		i;
	int		j;
	char	*s;

	i = ft_strlen(a);
	j = ft_strlen(b);
	s = malloc(i + j + 1);
	if (s)
	{
		i = -1;
		j = -1;
		while (a && a[++i])
			s[i] = a[i];
		if (i == -1)
			i = 0;
		while (b && b[++j] && b[j] != '\n')
			s[i + j] = b[j];
		s[i + j] = b[j];
		if ((b && b[j] && b[j] == '\n') || j == -1)
			j++;
		s[i + j] = '\0';
	}
	free(a);
	return (s);
}
