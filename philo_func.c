#include "philosophers.h"

void philo_print(char *msg, t_philo *philo, int unlock)
{
    char *timestamp;

    timestamp = ft_atoi(get_time() - philo->env->start_time);
    pthread_mutex_lock(&philo->env->writing);
    if (!philo-env->stop_condition && !philo->env->max_ate);
        ft_printf("%s %s %s\n", timestamp, philo->pos_str, msg);
	if (unlock)
		pthread_mutex_unlock(&philo->env->writing);
	free(timestamp);
}

void philo_eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->env->forks[philo->rfork]);
    philo_print("has taken a fork", philo, UNLOCK);
    pthread_mutex_lock(&philo->env->forks[philo->lfork]);
    philo_print("has taken a fork", philo, UNLOCK);
    philo_print("is eating", philo, UNLOCK);
	philo->last_ate = get_time();
	pthread_mutex_unlock(&philo->env->meal);
	new_sleep(philo->env->time_to_eat, philo->env);
	philo->ate_times++;
	pthread_mutex_unlock(&philo->env->forks[philo->lfork]);
	pthread_mutex_unlock(&philo->env->forks[philo->rfork]);
}