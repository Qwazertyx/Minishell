#include "../incl/minishell.h"

void	ft_exit(char ***tab, int i)
{
	int	nb;

	nb = 0;
	free_tab(tab);
	if (i > 0)
		if (tab && tab[i] && tab[i][1])
			nb = ft_atoi(tab[i][1]);
	exit(nb);
}
