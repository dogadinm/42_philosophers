#include "philosophers.h"

void *routine(void *params)
{
    t_philo *philo;
    t_env   *env;

    philo = (t_philo *)params;
    env = philo->env;
    if (philo->pos % 2 && env->count > 1)
        new_sleep(env->time_to_eat / 50, env);
    while (!env->stop_condition && !env->max_ate)
    {
        philo_eat(philo);
		philo_print("is sleeping", philo, UNLOCK);
		new_sleep(env->time_to_sleep, env);
		philo_print("is thinking", philo, UNLOCK);
	}
	return (NULL);
}


int	start_threads(t_env *env)
{
    int i;

    i = 0;
    env->start_time = get_time();
    while (i < env->count)
    {
        env->philos[i].last_ate = get_time();
        if (pthread_create(&env->philos[i].thread_id,
				NULL, routine, &(env->philos[i])))
            return (0);
        i++;
    }
}