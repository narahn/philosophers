#include "philo.h"

void philo_eat(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    pthread_mutex_lock(&philo->rules->print_mutex);
    printf("%ld %d has taken a fork\n",
        current_time_ms() - philo->rules->start_time, philo->id);
    pthread_mutex_unlock(&philo->rules->print_mutex);
    if (philo->rules->nb_philo == 1)
    {
        usleep(philo->rules->time_to_die * 1000);
        pthread_mutex_unlock(philo->left_fork);
        return;
    }
    pthread_mutex_lock(philo->right_fork);
    pthread_mutex_lock(&philo->rules->print_mutex);
    printf("%ld %d has taken a fork\n",
        current_time_ms() - philo->rules->start_time, philo->id);
    pthread_mutex_unlock(&philo->rules->print_mutex);
    pthread_mutex_lock(&philo->rules->print_mutex);
    printf("%ld %d is eating\n",
        current_time_ms() - philo->rules->start_time, philo->id);
    pthread_mutex_unlock(&philo->rules->print_mutex);
    philo->last_meal = current_time_ms();
    usleep(philo->rules->time_to_eat * 1000);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
    philo->meals_eaten++;
}


void philo_sleep_think(t_philo *philo)
{
    pthread_mutex_lock(&philo->rules->print_mutex);
    if (!philo->rules->someone_died)
        printf("%ld %d is sleeping\n",
            current_time_ms() - philo->rules->start_time, philo->id);
    pthread_mutex_unlock(&philo->rules->print_mutex);
    usleep(philo->rules->time_to_sleep * 1000);
    pthread_mutex_lock(&philo->rules->print_mutex);
    if (!philo->rules->someone_died)
        printf("%ld %d is thinking\n",
            current_time_ms() - philo->rules->start_time, philo->id);
    pthread_mutex_unlock(&philo->rules->print_mutex);
}

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    if (philo->id % 2 == 1)
        usleep(1000);
    while (!philo->rules->someone_died)
    {
        philo_eat(philo);
        if (philo->rules->someone_died)
            break;
        philo_sleep_think(philo);
    }
    return (NULL);
}
