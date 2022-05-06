#include "../incl/minishell.h"

int	stop_while(char c, char *legal)
{
	int	i;

	i = -1;
	while (legal[++i])
		if (legal[i] == c)
			return (1);
	return (0);
}

char	*ft_dolar(char *a, char **env)
{
	int		i;
	char	*s;
	char	*gete;

	i = 0;
	if (a[i] && a[i] == '?')
		return (ft_itoa((int)g_exit));
	dprintf(450, "SUS\n");
	while (a[i] && stop_while(a[i], \
	"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01233456789_"))
		i++;
	s = malloc(i + 1);
	if (!s)
		return (0);
	i = -1;
	while (a[++i] && stop_while(a[i], \
	"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01233456789_"))
		s[i] = a[i];
	s[i] = '\0';
	if (i != 0)
		gete = ft_strdup(ft_getenv(s, env));
	else
		gete = ft_strdup("$");
	free(s);
	return (gete);
}

int	skip_dolar(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] && cmd[i] == '?')
		return (1);
	while (cmd[i] && stop_while(cmd[i],
			"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01233456789_"))
		i++;
	return (i);
}
