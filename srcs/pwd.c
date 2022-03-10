#include "../incl/minishell.h"

void	ft_pwd()
{
	char	*a;

	a = NULL;
	a = getcwd(a, 1);
	printf("%s\n", a);
}
