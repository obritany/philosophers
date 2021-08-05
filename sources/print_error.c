#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
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
