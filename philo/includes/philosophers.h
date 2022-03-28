/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouali <ybouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 21:10:58 by ybouali           #+#    #+#             */
/*   Updated: 2022/02/17 21:40:51 by ybouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <errno.h>

# define MSG_FORK 1
# define MSG_EAT 2
# define MSG_SLEEP 3
# define MSG_THINK 4
# define MSG_DEAD 5
# define MSG_LIMIT 6

typedef pthread_mutex_t	t_mutex;

typedef struct s_params
{
	int		n_of_philo;
	int		t_sleep;
	int		t_eat;
	int		t_die;
	int		t_started;
	int		eat_limit;
	int		fed_amount;
	int		last_msg;
	t_mutex	m_stop;
	t_mutex	m_print;	
	t_mutex	*m_forks;
}			t_params;

typedef struct s_philo
{
	int			index;
	int			left_fork;
	int			right_fork;
	int			last_eat;
	int			t_wdead;
	int			eat_amount;
	t_mutex		m_eat;
	t_params	*params;
}			t_philo;	

int		init_all(t_philo **tmp, int argc, char *argv[]);

void	*routine_philo(void *arg);

void	eat(t_philo *philo);
void	put_forks(t_philo *philo);
void	take_forks(t_philo *philo);
int		check_arg(char **av);
void	print_msg(t_philo *philo, int type);
int		print_error(char *msg);
int		get_time(void);
void	ft_usleep(int n);

int		ft_atoi(const char *str);

#endif