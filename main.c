#include "philo.h"

int main(int argc, char **argv)
{
    t_rules rules;
    t_philo *philos;
    int i;
    pthread_t monitor;

    if (parse_args(argc, argv, &rules))
        return 1;
    if (init_all(&rules, &philos))
        return 1;
    rules.start_time = get_time_ms();
    i = 0;
    while (i < rules.nb_philo)
    {
        pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]);
        i++;
    }
    pthread_create(&monitor, NULL, monitor_routine, philos);
    i = 0;
    while (i < rules.nb_philo)
        pthread_join(philos[i++].thread, NULL);
    pthread_join(monitor, NULL);
    i = 0;
    while (i < rules.nb_philo)
        pthread_mutex_destroy(&rules.forks[i++]);
    pthread_mutex_destroy(&rules.print_mutex);
    pthread_mutex_destroy(&rules.death_mutex);
    pthread_mutex_destroy(&rules.meal_mutex);
    free(rules.forks);
    free(philos);
    return 0;
}
