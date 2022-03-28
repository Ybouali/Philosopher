/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouali <ybouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 21:10:47 by ybouali           #+#    #+#             */
/*   Updated: 2022/02/20 02:10:41 by ybouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_usleep(int n)
{
	struct timeval	start;
	struct timeval	step;

	gettimeofday(&start, NULL);
	while (1)
	{
		usleep(50);
		gettimeofday(&step, NULL);
		if (((step.tv_sec - start.tv_sec) * 1000000 \
			+ (step.tv_usec - start.tv_usec)) > n)
			break ;
	}
}

int	get_time(void)
{
	static struct timeval	time;
	int						ret;

	gettimeofday(&time, 0);
	ret = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ret);
}

int	print_error(char *msg)
{
	printf("Error\n%s.\n", msg);
	return (1);
}

static char	*get_msg(int type)
{
	if (type == MSG_FORK)
		return ("has taken a fork");
	else if (type == MSG_EAT)
		return ("is eating");
	else if (type == MSG_SLEEP)
		return ("is sleeping");
	else if (type == MSG_THINK)
		return ("is thinking");
	else if (type == MSG_DEAD)
		return ("died");
	return (" they eat enough");
}

void	print_msg(t_philo *philo, int type)
{
	pthread_mutex_lock(&philo->params->m_print);
	if (!philo->params->last_msg)
	{
		printf("%d", (get_time() - philo->params->t_started));
		if (type != MSG_LIMIT)
			printf(" %d ", philo->index + 1);
		printf("%s\n", get_msg(type));
		if (type == MSG_DEAD || type == MSG_LIMIT)
			philo->params->last_msg = 1;
	}
	pthread_mutex_unlock(&philo->params->m_print);
}
