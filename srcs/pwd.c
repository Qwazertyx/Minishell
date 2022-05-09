#include "../incl/minishell.h"

void	ft_pwd(void)
{
	char	*a;

	a = NULL;
	a = getcwd(a, 1);
	ft_putendl_fd(a, 1);
	free(a);
}
