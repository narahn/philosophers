#include "philo.h"

int parse_args (int argc, char **argv, t_rules *rules)
{
    if (argc != 5 && argc != 6)
    {
        printf("Usage: ./philo nb_philo time_to_die time_to_eat time_to_sleep [must_eat]\n");
        return(1);
    }
    rules->nb_philo = ft_atoi(argv[1]);
    rules->time_to_die = ft_atoi(argv[2]);
    rules->time_to_eat = ft_atoi(argv[3]);
    rules->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        rules->must_eat_count = ft_atoi(argv[5]);
    else
        rules->must_eat_count = -1;
    rules->someone_died = 0;
    if (rules->nb_philo <= 0 || rules->time_to_die <= 0
        || rules->time_to_eat <= 0 || rules->time_to_sleep <= 0
        || (argc == 6 && rules->must_eat_count <= 0))
    {
        printf("Error: invalide arguments\n");
        return(1);
    }
    return(0);
}
