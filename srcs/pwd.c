#include "../incl/minishell.h"

void	ft_pwd(t_var *tab)
{
	char	*a;

	a = NULL;
	a = getcwd(a, 1);
	// printf("%s\n", a);
	tab[0].output = ft_strdup(a);
}
