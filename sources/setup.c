#include "philo.h"

int	mutex_setup(t_rules *rules)
{
	int i;

	i = rules->nb_philo;
	while (i-- > 0)
		if (pthread_mutex_init(&(rules->forks[i]), NULL))
			return (1);
	if (pthread_mutex_init(&(rules->writing), NULL))
		return (1);
	if (pthread_mutex_init(&(rules->meal_check), NULL))
		return (1);
	return (0);
}

int	philo_setup(t_rules *rules)
{
	int i;

	i = rules->nb_philo;
	while (i-- > 0)
	{
		rules->philosophers[i].id = i;
		rules->philosophers[i].x_ate = 0;
		rules->philosophers[i].left_fork_id = i;
		rules->philosophers[i].right_fork_id = (i + 1) % rules->nb_philo;
		rules->philosophers[i].t_last_meal = 0;
		rules->philosophers[i].rules = rules;
	}
	return (0);
}

int	setup(t_rules *rules, char **argv)
{
	rules->nb_philo = ft_atoi(argv[1]);
	rules->time_death = ft_atoi(argv[2]);
	rules->time_eat = ft_atoi(argv[3]);
	rules->time_sleep = ft_atoi(argv[4]);
	rules->all_ate = 0;
	rules->dieded = 0;
	if (rules->nb_philo < 2 || rules->time_death < 0 || rules->time_eat < 0 ||
		rules->time_sleep < 0 || rules->nb_philo > 250)
		return (2);
	if (argv[5])
	{
		rules->nb_eat = ft_atoi(argv[5]);
		if (rules->nb_eat <= 0)
			return (2);
	}
	else
		rules->nb_eat = -1;
	if (mutex_setup(rules))
		return (3);
	philo_setup(rules);
	return (0);
}