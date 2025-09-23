#include "philo.h"

void print_action(t_philo *philo, char *msg)
{
    pthread_mutex_lock(&philo->rules->death_mutex);
    int dead = philo->rules->someone_died;
    pthread_mutex_unlock(&philo->rules->death_mutex);

    if (!dead)
    {
        pthread_mutex_lock(&philo->rules->print_mutex);
        printf("%ld %d %s\n", get_time_ms() - philo->rules->start_time, philo->id, msg);
        pthread_mutex_unlock(&philo->rules->print_mutex);
    }
}

void philo_eat(t_philo *philo)
{
    t_rules *rules = philo->rules;

    // Take forks
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->right_fork);
        print_action(philo, "has taken a fork");
        pthread_mutex_lock(philo->left_fork);
        print_action(philo, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(philo->left_fork);
        print_action(philo, "has taken a fork");
        pthread_mutex_lock(philo->right_fork);
        print_action(philo, "has taken a fork");
    }

    // --- Critical Section Start ---
    pthread_mutex_lock(&rules->meal_mutex);
    philo->last_meal = get_time_ms();

    philo->meals_eaten++;

    if (rules->must_eat_count > 0 && philo->meals_eaten == rules->must_eat_count)
    {
        pthread_mutex_lock(&rules->finished_mutex);
        rules->finished_eating++;
        pthread_mutex_unlock(&rules->finished_mutex);
    }
    pthread_mutex_unlock(&rules->meal_mutex);
    // --- Critical Section End ---

    print_action(philo, "is eating");
    smart_sleep(rules->time_to_eat, rules);

    // Release forks
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}
