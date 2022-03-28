/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouali <ybouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 21:10:37 by ybouali           #+#    #+#             */
/*   Updated: 2022/02/17 21:40:35 by ybouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	init_params_fill(t_params **tmp, int ac, char *av[])
{
	t_params	*ret;

	ret = *tmp;
	if (ac < 5 || ac > 6)
		return (print_error("Wrong amount of arguments"));
	ret->n_of_philo = ft_atoi(av[1]);
	if (ret->n_of_philo < 1 || ret->n_of_philo >= 200)
		return (print_error("Wrong amount of philosophers"));
	ret->t_die = ft_atoi(av[2]);
	if (ret->t_die < 60)
		return (print_error("Too short time to die"));
	ret->t_eat = ft_atoi(av[3]);
	if (ret->t_eat < 60)
		return (print_error("Too short time to eat"));
	ret->t_sleep = ft_atoi(av[4]);
	if (ret->t_sleep < 60)
		return (print_error("Too short time to sleep"));
	ret->eat_limit = 0;
	if (ac == 6)
		ret->eat_limit = ft_atoi(av[5]);
	if (ret->eat_limit < 0)
		return (print_error("Wrong eat limit"));
	ret->fed_amount = 0;
	ret->last_msg = 0;
	return (0);
}

static int	init_params(t_params **tmp, int ac, char *av[])
{
	t_params	*ret;

	ret = malloc(sizeof(t_params));
	if (!ret)
		return (print_error("Malloc error"));
	if (init_params_fill(&ret, ac, av))
	{
		free(ret);
		return (1);
	}
	ret->m_forks = malloc(sizeof(t_mutex) * ret->n_of_philo);
	if (!ret->m_forks)
	{
		free(ret);
		return (print_error("Malloc error"));
	}
	pthread_mutex_init(&ret->m_print, 0);
	pthread_mutex_init(&ret->m_stop, 0);
	pthread_mutex_lock(&ret->m_stop);
	*tmp = ret;
	return (0);
}

static int	init_philos(t_philo **tmp, t_params *params)
{
	t_philo		*ret;
	int			i;

	ret = malloc(sizeof(t_philo) * params->n_of_philo);
	if (!ret)
		return (1);
	i = 0;
	while (i < params->n_of_philo)
	{
		ret[i].index = i;
		ret[i].left_fork = i;
		ret[i].right_fork = (i + 1) % params->n_of_philo;
		ret[i].t_wdead = 0;
		ret[i].last_eat = 0;
		ret[i].params = params;
		ret[i].eat_amount = 0;
		pthread_mutex_init(&params->m_forks[i], 0);
		pthread_mutex_init(&ret[i].m_eat, 0);
		i++;
	}
	*tmp = ret;
	return (0);
}

int	init_all(t_philo **tmp, int ac, char *av[])
{
	t_philo		*ret;
	t_params	*params;

	params = 0;
	if (check_arg(av))
		return (1);
	if (init_params(&params, ac, av))
		return (1);
	if (init_philos(&ret, params))
		return (1);
	*tmp = ret;
	return (0);
}
