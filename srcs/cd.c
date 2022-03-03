#include "../incl/minishell.h"

int	mycd(char *cmd)
{
	if (cmd)
		chdir(cmd);
}
