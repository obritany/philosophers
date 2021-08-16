/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obritany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 15:04:51 by obritany          #+#    #+#             */
/*   Updated: 2021/08/16 15:04:54 by obritany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data	data;
	int		rslt;

	if (argc < 5 || argc > 6)
		return (print_error(1));
	rslt = setup(&data, argv);
	if (rslt)
		return (print_error(rslt));
	rslt = threads(&data);
	if (rslt)
		return (print_error(rslt));
	return (0);
}
