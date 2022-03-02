#include "../incl/minishell.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	p;
	int	c;

	i = 0;
	p = 1;
	c = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			p = p * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		c = c * 10 + (str[i] - 48);
		i++;
	}
	return (c * p);
}
