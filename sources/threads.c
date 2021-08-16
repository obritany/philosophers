#include "philo.h"

void	philo_eats(t_philosopher *philo)
{
	t_rules *rules;

	rules = philo->rules;
	pthread_mutex_lock(&(rules->forks[philo->left_fork_id]));
	action_print(rules, philo->id, "has taken a fork");
	pthread_mutex_lock(&(rules->forks[philo->right_fork_id]));
	action_print(rules, philo->id, "has taken a fork");
	pthread_mutex_lock(&(rules->meal_check));
	action_print(rules, philo->id, "is eating");
	philo->t_last_meal = millis();
	pthread_mutex_unlock(&(rules->meal_check));
	smart_sleep(rules, rules->time_eat);
	(philo->x_ate)++;
	pthread_mutex_unlock(&(rules->forks[philo->left_fork_id]));
	pthread_mutex_unlock(&(rules->forks[philo->right_fork_id]));
}

void	*p_thread(void *void_philosopher)
{
	int				i;
	t_philosopher	*philo;
	t_rules			*rules;

	i = 0;
	philo = (t_philosopher *)void_philosopher;
	rules = philo->rules;
	if (philo->id % 2)
		usleep(15000);
	while (!(rules->dieded))
	{
		philo_eats(philo);
		if (rules->all_ate)
			break ;
		action_print(rules, philo->id, "is sleeping");
		smart_sleep(rules, rules->time_sleep);
		action_print(rules, philo->id, "is thinking");
		i++;
	}
	return (NULL);
}

void	wait_threads(t_rules *rules)
{
	int i;

	i = -1;
	while (++i < rules->nb_philo)
		pthread_join(rules->philosophers[i].thread_id, NULL);
	i = -1;
	while (++i < rules->nb_philo)
		pthread_mutex_destroy(&(rules->forks[i]));
	pthread_mutex_destroy(&(rules->writing));
}

void	death_checker(t_rules *rules)
{
	int i;

	while (!(rules->all_ate))
	{
		i = 0;
		while (i < rules->nb_philo && !(rules->dieded))
		{
			pthread_mutex_lock(&(rules->meal_check));
			if ((millis() - rules->philosophers[i].t_last_meal) > rules->time_death)
			{
				action_print(rules, i, "died");
				rules->dieded = 1;
			}
			pthread_mutex_unlock(&(rules->meal_check));
			usleep(100);
			i++;
		}
		if (rules->dieded)
			break ;
		i = 0;
		while (rules->nb_eat != -1 && i < rules->nb_philo && rules->philosophers[i].x_ate >= rules->nb_eat)
			i++;
		if (i == rules->nb_philo)
			rules->all_ate = 1;
	}
}

int	threads(t_rules *rules)
{
	int	i;

	rules->first_timestamp = millis();
	i = 0;
	while (i < rules->nb_philo)
	{
		if (pthread_create(&(rules->philosophers[i].thread_id), NULL, p_thread, &(rules->philosophers[i])))
			return (1);
		rules->philosophers[i].t_last_meal = millis();
		i++;
	}
	death_checker(rules);
	wait_threads(rules);
	return (0);
}
