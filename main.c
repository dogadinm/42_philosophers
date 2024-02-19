/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdogadin <mdogadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:25:52 by mdogadin          #+#    #+#             */
/*   Updated: 2024/02/13 14:25:52 by mdogadin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_check_arg(t_info *info, int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_atoi(av[i]) <= 0)
			return (0);
		i++;
	}
	info->count = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		info->eat_count_max = ft_atoi(av[5]);
	else
		info->eat_count_max = 0;
	if (info->count < 1 || info->time_to_die < 0 || info->time_to_eat < 0
		|| info->time_to_sleep < 0 || info->eat_count_max < 0)
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_info	info;

	info.max_ate = 0;
	info.stop_condition = 0;
	if (ac < 5 || ac > 6)
		return (ft_error("Should be : ./philo <# philosophers> <time to die> <time to eat>\
 <time to sleep> [# times each philosopher must eat]\n"));
	if (!ft_check_arg(&info, ac, av))
		return (ft_error("Error\n"));
	if (!ft_init(&info))
		return (ft_error("init error.\n"));
	if (!start_threads(&info))
		return (ft_error("Error\n"));
}
