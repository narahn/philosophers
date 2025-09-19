# include "philo.h"

void cleanup(t_rules *rules)
{
    int i;

    if (rules->forks)
    {
        i = 0;
        while (i < rules->nb_philo)
        {
            pthread_mutex_destroy(&rules->forks[i]);
            i++;
        }
        free(rules->forks);
        rules->forks = NULL;
    }
    pthread_mutex_destroy(&rules->finished_mutex);
    pthread_mutex_destroy(&rules->print_mutex);
    if (rules->philos)
    {
        free(rules->philos);
        rules->philos = NULL;
    }
}
