#include "../incl/minishell.h"

int	is_num(char *a)
{
	int	i;

	i = 0;
	if (a[i] == '+' || a[i] == '-')
		i++;
	while (a[i] && a[i] >= '0' && a[i] <= '9')
		i++;
	if (!a[i])
		return (1);
	return (0);
}

int	ft_strleni(char *a, int i)
{
	int	j;

	j = i;
	while (a[i])
		i++;
	return (i - j);
}

int	ft_strcmpi(char *a, char *b, int i)
{
	int	j;

	j = 0;
	while (a[i] && b[j] && a[i] == b[j])
		i += 1 + 0 * j++;
	return (a[i] - b[j]);
}

int verif_exit(char *cmd)
{
	char	sign;

	sign = 0;
	if (cmd && cmd[0] == '-')
		sign += 2;
	if (cmd && cmd[0] == '+')
		sign++;
	if (cmd && (ft_strleni(cmd, sign) > 19
		|| (ft_strleni(cmd, sign) == 19 \
		&& ft_strcmpi(cmd, "9223372036854775807", sign) > 0 && sign <= 1) \
		|| (ft_strlen(cmd) == 20 && ft_strcmp(cmd, "-9223372036854775808") > 0 \
		&& sign == 2) || !is_num(cmd)))
	{
		ft_putstr_fd("Minishell: exit: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (0);
	}
	return (1);
}

long long	ft_atol(char *str)
{
	int			i;
	int			sign;
	long long	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while (str && (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r')))
		i++;
	if (str && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str && str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb * sign);
}

void	ft_exit(t_var	*tab, int i)
{
	int		nb;
	char	**cmd;

	nb = -1;
	cmd = NULL;
	if (tab && tab->cmd[i] && tab->cmd[i][1])
	{
		dprintf(2, "sus\n");
		cmd = ft_splitve(tab->cmd[i][1], ' ', tab->cmd[i][0]);
		int	i = 0;
		while (cmd && cmd[i])
			printf("cmd[%d] = %s\n", i, cmd[i++]);
		if (!verif_exit(cmd[1]))
			nb = 255;
		else
			nb = ft_atol(cmd[1]);
	}
	else if (tab && tab->cmd[i])
	{
		free_struc(tab, 0);
		exit(0);
	}
	if ((cmd && cmd[1] && !cmd[2]))
	{
		free_struc(tab, 0);
		exit(nb % 256);
	}
	ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
}
