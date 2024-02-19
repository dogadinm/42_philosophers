/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdogadin <mdogadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:48:47 by mdogadin          #+#    #+#             */
/*   Updated: 2024/02/13 14:48:47 by mdogadin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned int	ft_time_now(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (unsigned long)1000) + (time.tv_usec / 1000));
}

void	ft_sleep(unsigned long duration, t_info *info)
{
	unsigned long	start;

	start = ft_time_now();
	while (!info->stop_condition)
	{
		if (ft_time_now() - start >= duration)
			break ;
		usleep(1);
	}
}

int	ft_error(char *mess)
{
	ft_putstr_fd(mess, 2);
	return (0);
}
