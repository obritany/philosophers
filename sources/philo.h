/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obritany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 15:04:43 by obritany          #+#    #+#             */
/*   Updated: 2021/08/16 15:04:45 by obritany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	pthread_t			thread_id;
	int					id;
	int					left_fork;
	int					right_fork;
	int					meal_count;
	long long			last_meal_time;
	struct s_data		*data;
}						t_philo;

typedef struct s_data
{
	int					num_philos;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					num_meal;
	int					philo_died;
	int					meals_done;
	long long			start_millis;
	pthread_mutex_t		check_meal;
	pthread_mutex_t		forks[300];
	pthread_mutex_t		printing;
	t_philo				philos[300];
}						t_data;

int			ft_atoi(const char *str);
void		ft_putstr_fd(char *s, int fd);
int			setup(t_data *data, char **argv);
int			threads(t_data *data);
long long	millis(void);
void		sleep_millis(t_data *data, long long time);
void		print_event(t_data *data, int id, char *string);
int			print_error(int error);

#endif
