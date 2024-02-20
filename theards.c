/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   theards.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdogadin <mdogadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:51:01 by mdogadin          #+#    #+#             */
/*   Updated: 2024/02/13 14:51:01 by mdogadin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *params)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)params;
	info = philo->info;
	if (philo->pos % 2 && info->count > 1)
		ft_sleep(info->time_to_eat / 50, info);
	while (!info->stop_condition && !info->max_ate)
	{
		eat(philo);	
		print_msg("is sleeping", philo, UNLOCK);
		ft_sleep(info->time_to_sleep, info);
		print_msg("is thinking", philo, UNLOCK);
		if (info->eat_count_max)
		{
			if (philo->ate_times >= info->eat_count_max)
				break;
		}
	}
	return (NULL);
}

static void	exit_threads(t_info *info)
{
	int	i;

	if (info->count == 1)
		pthread_detach(info->philos[0].thread_id);
	else
	{
		i = -1;
		while (++i < info->count)
			pthread_join(info->philos[i].thread_id, NULL);
	}
	i = -1;
	while (++i < info->count)
		pthread_mutex_destroy(&info->forks[i]);
	pthread_mutex_destroy(&info->meal);
	pthread_mutex_destroy(&info->writing);
	i = -1;
	while (++i < info->count)
		free(info->philos[i].pos_str);
	free(info->philos);
	free(info->forks);
}

int	start_threads(t_info *info)
{
	int	i;

	i = 0;
	info->start_time = ft_time_now();
	while (i < info->count)
	{
		info->philos[i].last_ate = ft_time_now();
		if (pthread_create(&info->philos[i].thread_id,
				NULL, routine, &(info->philos[i])))
			return (0);
		i++;
	}
	death(info, info->philos);
	pthread_mutex_unlock(&info->writing);
	exit_threads(info);
	return (1);
}
