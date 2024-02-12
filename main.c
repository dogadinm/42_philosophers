#include "philosophers.h"

int ft_check_arg(t_env *env, int ac, char **av)
{
    int i;
    i = 1;
    while (i < ac)
    {
		if (ft_atoi(av[i]) <= 0)
			return (0);
        i++;
    }
	env->count = ft_atoi(av[1]);
	env->time_to_die = ft_atoi(av[2]);
	env->time_to_eat = ft_atoi(av[3]);
	env->time_to_sleep = ft_atoi(av[4]);
    if (ac == 6)
		env->eat_count_max = ft_atoi(av[5]);
    else
        env->eat_count_max = 0;
    if (env->count < 1 || env->time_to_die < 0 || env->time_to_eat < 0
		|| env->time_to_sleep < 0 || env->eat_count_max < 0)
		return (0);
    return (1);
}

int main(int ac, char **av)
{
    t_env env;

    env.max_ate = 0;
    env.stop_condition = 0;
    if (ac < 5 || ac > 6)
        return(ft_error("Should be : ./philo <# philosophers> <time to die> <time to eat>\
 <time to sleep> [# times each philosopher must eat]\n"));
    if (!ft_check_arg(&env, ac, av))
        return(ft_error("Error\n"));
    if (!ft_init(&env))
		return (ft_return_error("init error.\n"));
    if (!start_threads(&env))
        return(ft_error("Error\n"));
}