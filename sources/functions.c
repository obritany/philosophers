/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obritany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 15:04:30 by obritany          #+#    #+#             */
/*   Updated: 2021/08/16 15:04:32 by obritany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	millis(void)
{
	struct timeval	time;
	long long		rslt;

	gettimeofday(&time, NULL);
	rslt = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (rslt);
}

void	msleep(t_data *data, long long sleep_time)
{
	long long	start;

	start = millis();
	while (!(data->philo_died))
	{
		if ((millis() - start) >= sleep_time)
			break ;
		usleep(100);
	}
}

void	print_event(t_data *data, int id, char *event)
{
	pthread_mutex_lock(&(data->printing));
	if (!(data->philo_died))
		printf("%lli %i %s\n", millis() - data->start_millis, id + 1, event);
	pthread_mutex_unlock(&(data->printing));
	return ;
}

int	print_error(int error)
{
	if (error == 1)
		ft_putstr_fd("Error: Wrong number of arguments\n", 2);
	if (error == 2)
		ft_putstr_fd("Error: Wrong argument\n", 2);
	if (error == 3)
		ft_putstr_fd("Error: Mutex problem\n", 2);
	if (error == 4)
		ft_putstr_fd("Error: Thread problem\n", 2);
	return (error);
}
