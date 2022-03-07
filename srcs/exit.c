#include "../incl/minishell.h"

void	ft_exit(char ***tab, int i)
{
	int	nb;

	nb = 0;
	if (tab && tab[i] && tab[i][1])
		nb = ft_atoi(tab[i][1]);
	free_tab(tab);
	exit(nb);
}
