#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

pthread_mutex_t	mutex;

long long	millis(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec);
}

void	*print_num(void *count)
{
	pthread_mutex_lock(&mutex);

	for (int i = 0; i < *((int*)count); i++)
	{
		printf("%d", i);
		fflush(stdout);
		sleep(1);
	}

	pthread_mutex_unlock(&mutex);
	
	return (NULL);
}

int	main()
{
	int count;
	pthread_t id1;
	pthread_t id2;

	printf("Hello!\n");
	printf("Time: %lld\n", millis());

	count = 5;
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&id1, NULL, print_num, &count);
	pthread_create(&id2, NULL, print_num, &count);

	pthread_join(id1, NULL);
	pthread_join(id2, NULL);

	printf("\n");
}