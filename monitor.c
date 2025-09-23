#include "philo.h"

// Check if all philosophers finished eating
int all_finished(t_philo *philos, t_rules *rules)
{
    int i = 0;
    int finished = 1;

    while (i < rules->nb_philo)
    {
        pthread_mutex_lock(&rules->meal_mutex);
        if (philos[i].meals_eaten < rules->must_eat_count)
            finished = 0;
        pthread_mutex_unlock(&rules->meal_mutex);
        i++;
    }
    return finished;
}

int check_death(t_philo *philo)
{
    long last;

    // Protect last_meal
    pthread_mutex_lock(&philo->rules->meal_mutex);
    last = philo->last_meal;
    pthread_mutex_unlock(&philo->rules->meal_mutex);

    long now = get_time_ms();

    if (now - last > philo->rules->time_to_die)
    {
        pthread_mutex_lock(&philo->rules->death_mutex);
        if (!philo->rules->someone_died)
        {
            philo->rules->someone_died = 1;
            pthread_mutex_lock(&philo->rules->print_mutex);
            printf("%ld %d died\n", now - philo->rules->start_time, philo->id);
            pthread_mutex_unlock(&philo->rules->print_mutex);
        }
        pthread_mutex_unlock(&philo->rules->death_mutex);
        return 1;
    }
    return 0;
}

void *monitor_routine(void *arg)
{
    t_philo *philos = (t_philo *)arg;
    t_rules *rules = philos[0].rules;
    int i;

    while (1)
    {
        i = 0;
        while (i < rules->nb_philo)
        {
            if (check_death(&philos[i]))
                return NULL;
            i++;
        }

        if (rules->must_eat_count > 0 && all_finished(philos, rules))
            return NULL;

        usleep(1000);
    }
}
