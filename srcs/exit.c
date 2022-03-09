#include "../incl/minishell.h"

void	ft_exit(t_var	*tab, int i)
{
	int	nb;

	nb = 0;
	if (tab && tab[i].cmd && tab[i].cmd[1])
		nb = ft_atoi(tab[i].cmd[1]);
	free_tab(tab);
	exit(nb);
}
