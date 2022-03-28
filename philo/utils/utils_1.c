/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouali <ybouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 21:13:44 by ybouali           #+#    #+#             */
/*   Updated: 2022/02/17 21:41:45 by ybouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	ft_sheck_and_return_nbr(char *str, int sign)
{
	int		index;
	int		res;

	res = 0;
	index = 0;
	while (str[index] >= '0' && str[index] <= '9')
	{
		res = (res * 10) + (str[index] - 48);
		index++;
	}
	if (index > 19 && sign == -1)
		return (0);
	if (index > 19 && sign == 1)
		return (-1);
	return (res * sign);
}

int	ft_atoi(const char *str)
{
	int		index;
	int		sign;
	int		ret;

	ret = 0;
	index = 0;
	sign = 1;
	while ((str[index] >= 9 && str[index] <= 13) || str[index] == ' ')
		index++;
	if (str[index] == '-' || str[index] == '+')
	{
		if (str[index] == '-')
			sign = -1;
		index++;
	}
	ret = ft_sheck_and_return_nbr((char *)str + index, sign);
	return (ret);
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	check_arg(char **av)
{
	int		i;
	int		j;

	i = 0;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
		{
			if (!ft_isdigit(av[i][j]))
				return (print_error("all args shoud be a number character"));
		}
	}
	return (0);
}
