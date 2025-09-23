#include "philo.h"

int init_all(t_rules *rules, t_philo **philos)
{
    int i;

    rules->forks = malloc(sizeof(pthread_mutex_t) * rules->nb_philo);
    if (!rules->forks)
        return 1;
    i = 0;
    while (i < rules->nb_philo)
        pthread_mutex_init(&rules->forks[i++], NULL);
    pthread_mutex_init(&rules->print_mutex, NULL);
    pthread_mutex_init(&rules->death_mutex, NULL);
    pthread_mutex_init(&rules->meal_mutex, NULL);
    *philos = malloc(sizeof(t_philo) * rules->nb_philo);
    if (!(*philos))
        return 1;
    i = 0;
    while (i < rules->nb_philo)
    {
        (*philos)[i].id = i + 1;
        (*philos)[i].meals_eaten = 0;
        (*philos)[i].last_meal = get_time_ms();
        (*philos)[i].rules = rules;
        (*philos)[i].left_fork = &rules->forks[i];
        (*philos)[i].right_fork = &rules->forks[(i + 1) % rules->nb_philo];
        i++;
    }
    return 0;
}
