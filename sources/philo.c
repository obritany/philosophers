#include "philo.h"

int		main(int argc, char *argv[])
{
	t_rules	rules;
	int		ret;

	if (argc < 5 || argc > 6)
		return (print_error(1));
	if ((ret = setup(&rules, argv)))
		return (print_error(ret));
	if (threads(&rules))
		return (print_error(4));
	return (0);
}
