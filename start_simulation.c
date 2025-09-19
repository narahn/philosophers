#include "philo.h"

void start_simulation(t_rules *rules)
{
    int i;
    pthread_t monitor_thread;

    rules->start_time = current_time_ms();
    i = 0;
    while (i < rules->nb_philo)
    {
        pthread_create(&rules->philos[i].thread, NULL, philo_routine, &rules->philos[i]);
        i++;
    }
    pthread_create(&monitor_thread, NULL, monitor, rules);
    i = 0;
    while (i < rules->nb_philo)
    {
        pthread_join(rules->philos[i].thread, NULL);
        i++;
    }
    pthread_join(monitor_thread, NULL);
}
