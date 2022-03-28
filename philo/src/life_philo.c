/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouali <ybouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 21:10:26 by ybouali           #+#    #+#             */
/*   Updated: 2022/02/19 00:35:26 by ybouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->params->m_forks[philo->left_fork]);
	print_msg(philo, MSG_FORK);
	pthread_mutex_lock(&philo->params->m_forks[philo->right_fork]);
	print_msg(philo, MSG_FORK);
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->params->m_forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->params->m_forks[philo->right_fork]);
	print_msg(philo, MSG_SLEEP);
	ft_usleep(philo->params->t_sleep * 1000);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_eat);
	philo->last_eat = get_time();
	philo->t_wdead = philo->last_eat + philo->params->t_die;
	if (philo->params->eat_limit != 0 \
			&& philo->eat_amount == philo->params->eat_limit)
		return ;
	philo->eat_amount++;
	if (philo->eat_amount >= philo->params->eat_limit)
		philo->params->fed_amount++;
	print_msg(philo, MSG_EAT);
	ft_usleep(philo->params->t_eat * 1000);
	pthread_mutex_unlock(&philo->m_eat);
}
