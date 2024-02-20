/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdogadin <mdogadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:45:41 by mdogadin          #+#    #+#             */
/*   Updated: 2024/02/13 14:45:41 by mdogadin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include "./libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define UNLOCK 1
# define LOCK 0

struct	s_info;

typedef struct s_philo
{
	int				ate_times;
	int				pos;
	char			*pos_str;
	int				rfork;
	int				lfork;
	unsigned long	last_ate;
	struct s_info	*info;
	pthread_t		thread_id;
}				t_philo;

typedef struct s_info
{
	int				count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count_max;
	unsigned long	start_time;
	int				stop_condition;
	int				max_ate;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	meal;
	pthread_mutex_t	writing;
}				t_info;

int				ft_error(char *mess);
int				start_threads(t_info *info);
int				ft_init(t_info *info);
void			ft_sleep(unsigned long duration, t_info *info);
void			print_msg(char *msg, t_philo *philo, int unlock);
void			death(t_info *info, t_philo *philo);
void			eat(t_philo *philo);
unsigned int	ft_time_now(void);

#endif