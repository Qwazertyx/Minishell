#include "../incl/minishell.h"

char	*ft_join(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while(s2[j])
		j++;
	s = malloc(i + j + 1);
	i = -1;
	j = 0;
	while (s1[++i])
		s[i] = s1[i];
	while (s2[++j])
		s[i + j] = s2[j];
	s[i + j] = '\0';

}