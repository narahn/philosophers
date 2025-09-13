#include "philo.h"

int init_mutexes(t_rules *rules)
{
    int i;

    rules->forks = malloc(sizeof(pthread_mutex_t) * rules->nb_philo);
    if (!rules->forks)
        return (1);
    i = 0;
    while (i < rules->nb_philo)
    {
        if (pthread_mutex_init(&rules->forks[i], NULL) != 0)
            return (1);
        i++;
    }
    if (pthread_mutex_init(&rules->print_mutex, NULL) != 0)
        return (1);
    return (0);
}

void destroy_mutexes(t_rules *rules)
{
    int i = 0;
    while (i < rules->nb_philo)
    {
        pthread_mutex_destroy(&rules->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&rules->print_mutex);
    free(rules->forks);
}

void init_philosophers(t_rules *rules, t_philo *philos)
{
    int i;
    long now;

    i = 0;
    now = current_time_ms();
    while (i < rules->nb_philo)
    {
        philos[i].id = i + 1;
        philos[i].rules = rules;
        philos[i].left_fork = &rules->forks[i];
        philos[i].right_fork = &rules->forks[(i + 1) % rules->nb_philo];
        philos[i].meals_eaten = 0;
        philos[i].last_meal = now;
        i++;
    }
}

void free_philos(t_philo *philos)
{
    if (philos)
        free(philos);
}
