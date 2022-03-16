#include "../incl/minishell.h"

void	ft_exit(t_var	*tab, int i)
{
	int	nb;

	nb = 0;
	if (tab && tab->cmd[i] && tab->cmd[i][1])
		nb = ft_atoi(tab->cmd[i][1]);
	free_tab(tab);
	exit(nb);
}
