/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obritany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 15:05:19 by obritany          #+#    #+#             */
/*   Updated: 2021/08/16 15:05:21 by obritany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_meal(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&(data->forks[philo->left_fork]));
	print_event(data, philo->id, "has taken a fork");
	pthread_mutex_lock(&(data->forks[philo->right_fork]));
	print_event(data, philo->id, "has taken a fork");
	pthread_mutex_lock(&(data->meal_state));
	print_event(data, philo->id, "is eating");
	philo->last_meal_time = millis();
	pthread_mutex_unlock(&(data->meal_state));
	msleep(data, data->time_eat);
	(philo->meal_count)++;
	pthread_mutex_unlock(&(data->forks[philo->left_fork]));
	pthread_mutex_unlock(&(data->forks[philo->right_fork]));
}

void	*philo_thread(void *void_philosopher)
{
	int		i;
	t_philo	*philo;
	t_data	*data;

	i = 0;
	philo = (t_philo *)void_philosopher;
	data = philo->data;
	if (philo->id % 2)
		usleep(10000);
	while (!(data->philo_died))
	{
		philo_meal(philo);
		if (data->meals_done)
			break ;
		print_event(data, philo->id, "is sleeping");
		msleep(data, data->time_sleep);
		print_event(data, philo->id, "is thinking");
		i++;
	}
	return (NULL);
}

void	wait_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
		pthread_join(data->philos[i].thread_id, NULL);
	i = -1;
	while (++i < data->num_philos)
		pthread_mutex_destroy(&(data->forks[i]));
	pthread_mutex_destroy(&(data->printing));
}

void	check_status(t_data *data)
{
	int	i;

	while (!(data->meals_done))
	{
		i = -1;
		while (++i < data->num_philos && !(data->philo_died))
		{
			pthread_mutex_lock(&(data->meal_state));
			if ((millis() - data->philos[i].last_meal_time) > data->time_die)
			{
				print_event(data, i, "died");
				data->philo_died = 1;
			}
			pthread_mutex_unlock(&(data->meal_state));
			usleep(100);
		}
		if (data->philo_died)
			break ;
		i = 0;
		while (data->num_meal != -1 && i < data->num_philos
			&& data->philos[i].meal_count >= data->num_meal)
			i++;
		if (i == data->num_philos)
			data->meals_done = 1;
	}
}

int	threads(t_data *data)
{
	int	i;

	data->start_millis = millis();
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&(data->philos[i].thread_id), NULL,
				philo_thread, &(data->philos[i])))
			return (4);
		data->philos[i].last_meal_time = millis();
		i++;
	}
	check_status(data);
	wait_threads(data);
	return (0);
}
