/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obritany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 15:05:00 by obritany          #+#    #+#             */
/*   Updated: 2021/08/16 15:05:02 by obritany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_setup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&(data->printing), NULL))
		return (1);
	if (pthread_mutex_init(&(data->meal_state), NULL))
		return (1);
	return (0);
}

int	philos_setup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i;
		data->philos[i].meal_count = 0;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->num_philos;
		data->philos[i].last_meal_time = 0;
		data->philos[i].data = data;
		i++;
	}
	return (0);
}

int	setup(t_data *data, char **argv)
{
	data->num_philos = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	data->meals_done = 0;
	data->philo_died = 0;
	if (data->num_philos < 1 || data->time_die < 0 || data->time_eat < 0
		|| data->time_sleep < 0 || data->num_philos > 300)
		return (2);
	if (argv[5])
	{
		data->num_meal = ft_atoi(argv[5]);
		if (data->num_meal <= 0)
			return (2);
	}
	else
		data->num_meal = -1;
	if (mutex_setup(data))
		return (3);
	philos_setup(data);
	return (0);
}
