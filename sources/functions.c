#include "philo.h"

int	ft_atoi(const char *str)
{
	unsigned long long	pre_max;
	unsigned long long	rslt;
	int	sign;
	int	i;

	pre_max = 922337203685477580;
	rslt = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (sign == 1)
			if (rslt > pre_max || (rslt == pre_max && str[i] > '7'))
				return (-1);
		if (sign == -1)
			if (rslt > pre_max || (rslt == pre_max && str[i] > '8'))
				return (0);
		rslt = (rslt * 10) + (str[i++] - '0');
	}
	return (rslt * sign);
}

long long	millis(void)
{
	struct timeval	time;
	long long rslt;

	gettimeofday(&time, NULL);
	rslt = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (rslt);
}

void	smart_sleep(t_rules *rules, long long time)
{
	long long i;

	i = millis();
	while (!(rules->dieded))
	{
		if ((millis() - i) >= time)
			break ;
		usleep(50);
	}
}

void	action_print(t_rules *rules, int id, char *string)
{
	pthread_mutex_lock(&(rules->writing));
	if (!(rules->dieded))
	{
		printf("%lli ", millis() - rules->first_timestamp);
		printf("%i ", id + 1);
		printf("%s\n", string);
	}
	pthread_mutex_unlock(&(rules->writing));
	return ;
}
