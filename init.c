/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdogadin <mdogadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:25:10 by mdogadin          #+#    #+#             */
/*   Updated: 2024/02/13 14:25:10 by mdogadin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_init_mutex(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->count)
	{
		if (pthread_mutex_init(&(info->forks[i]), NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&info->meal, NULL))
		return (1);
	if (pthread_mutex_init(&info->writing, NULL))
		return (1);
	return (0);
}

int	ft_init_philo(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->count)
	{
		info->philos[i].ate_times = 0;
		info->philos[i].pos = i + 1;
		info->philos[i].pos_str = ft_itoa(i + 1);
		if (!info->philos[i].pos_str)
			break ;
		info->philos[i].rfork = i;
		info->philos[i].lfork = (i + 1) % info->count;
		info->philos[i].info = info;
		i++;
	}
	if (i != info->count)
	{
		while (i >= 0)
		{
			free(info->philos[i].pos_str);
			i--;
		}
		return (1);
	}
	return (0);
}

int	ft_init(t_info *info)
{
	info->philos = malloc(sizeof(t_philo) * info->count);
	if (!info->philos)
		return (0);
	info->forks = malloc(sizeof(pthread_mutex_t) * info->count);
	if (!info->forks)
	{
		free(info->philos);
		return (0);
	}
	if (ft_init_mutex(info))
	{
		free(info->philos);
		free(info->forks);
		return (0);
	}
	if (ft_init_philo(info))
	{
		free(info->philos);
		free(info->forks);
		return (0);
	}
	return (1);
}
