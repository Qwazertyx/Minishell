/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:04:58 by mlagrang          #+#    #+#             */
/*   Updated: 2022/07/19 13:04:59 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	verif_exit(char *cmd)
{
	char	sign;

	sign = 0;
	if (cmd && cmd[0] == '-')
		sign += 2;
	if (cmd && cmd[0] == '+')
		sign++;
	if (cmd && ((!cmd[1] && sign != 0) || (ft_strleni(cmd, sign) > 19 \
		|| (ft_strleni(cmd, sign) == 19 \
		&& ft_strcmpi(cmd, "9223372036854775807", sign) > 0 && sign <= 1) \
		|| (ft_strlen(cmd) == 20 && ft_strcmp(cmd, "-9223372036854775808") > 0 \
		&& sign == 2) || !is_num(cmd))))
	{
		ft_putstr_fd("Minishell: exit: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (0);
	}
	return (1);
}

long	ft_atol(char *str)
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

void	ft_exit(t_var	*tab, int i, int nb, char **cmd)
{
	if (tab && tab->cmd[i] && tab->cmd[i][1])
	{
		cmd = ft_splitve(tab->cmd[i][1], ' ', tab->cmd[i][0]);
		if (!cmd)
			return (ft_putstr_fd("malloc error\n", 2));
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
		free_split(cmd);
		free_struc(tab, 0);
		exit(nb % 256);
	}
	free_split(cmd);
	ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
}
