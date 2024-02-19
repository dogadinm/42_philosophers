/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdogadin <mdogadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:50:23 by mdogadin          #+#    #+#             */
/*   Updated: 2024/02/13 14:50:23 by mdogadin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_msg(char *msg, t_philo *philo, int unlock)
{
	char	*timestamp;

	timestamp = ft_itoa(ft_time_now() - philo->info->start_time);
	pthread_mutex_lock(&philo->info->writing);
	if (!philo->info->stop_condition && !philo->info->max_ate)
		ft_printf("%s %s %s\n", timestamp, philo->pos_str, msg);
	if (unlock)
		pthread_mutex_unlock(&philo->info->writing);
	free(timestamp);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->forks[philo->rfork]);
	print_msg("has taken a fork", philo, UNLOCK);
	pthread_mutex_lock(&philo->info->forks[philo->lfork]);
	print_msg("has taken a fork", philo, UNLOCK);
	print_msg("is eating", philo, UNLOCK);
	philo->last_ate = ft_time_now();
	ft_sleep(philo->info->time_to_eat, philo->info);
	
	
	philo->ate_times++;
	pthread_mutex_unlock(&philo->info->forks[philo->lfork]);
	pthread_mutex_unlock(&philo->info->forks[philo->rfork]);
}

void	death(t_info *info, t_philo *philo)
{
	int	i;

	while (!info->max_ate)
	{
		i = -1;
		while (++i < info->count && !info->stop_condition)
		{
			pthread_mutex_lock(&info->meal);
			if ((int)(ft_time_now() - philo[i].last_ate) >= info->time_to_die)
			{
				print_msg("died", &philo[i], LOCK);
				info->stop_condition = 1;
			}
			pthread_mutex_unlock(&info->meal);
		}
		if (info->stop_condition)
			break ;
		i = 0;
		while (info->eat_count_max && i < info->count
			&& philo[i].ate_times >= info->eat_count_max)
			i++;
		info->max_ate = (i == info->count);
	}
}
