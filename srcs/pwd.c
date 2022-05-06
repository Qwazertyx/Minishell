#include "../incl/minishell.h"

void	ft_pwd(void)
{
	char	*a;

	a = NULL;
	a = getcwd(a, 1);
	printf("%s\n", a);
}
