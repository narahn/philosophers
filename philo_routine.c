#include "philo.h"

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    t_rules *rules = philo->rules;

    if (rules->nb_philo == 1)
    {
        print_action(philo, "has taken a fork");
        smart_sleep(rules->time_to_die, rules);
        print_action(philo, "died");
        pthread_mutex_lock(&rules->death_mutex);
        rules->someone_died = 1;
        pthread_mutex_unlock(&rules->death_mutex);
        return NULL;
    }

    while (1)
    {
        pthread_mutex_lock(&rules->death_mutex);
        int dead = rules->someone_died;
        pthread_mutex_unlock(&rules->death_mutex);
        if (dead)
            break;

        pthread_mutex_lock(&rules->finished_mutex);
        int done = (rules->must_eat_count > 0 &&
                    rules->finished_eating == rules->nb_philo);
        pthread_mutex_unlock(&rules->finished_mutex);
        if (done)
            break;

        philo_eat(philo);

        pthread_mutex_lock(&rules->death_mutex);
        dead = rules->someone_died;
        pthread_mutex_unlock(&rules->death_mutex);
        if (dead)
            break;

        print_action(philo, "is sleeping");
        smart_sleep(rules->time_to_sleep, rules);

        pthread_mutex_lock(&rules->death_mutex);
        dead = rules->someone_died;
        pthread_mutex_unlock(&rules->death_mutex);
        if (dead)
            break;

        print_action(philo, "is thinking");
    }
    return NULL;
}
