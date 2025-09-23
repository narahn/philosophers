#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_rules t_rules;

typedef struct s_philo
{
    int             id;
    int             meals_eaten;
    long            last_meal;
    pthread_t       thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_rules         *rules;
}               t_philo;

struct s_rules
{
    int             nb_philo;
    long            time_to_die;
    long            time_to_eat;
    long            time_to_sleep;
    int             must_eat_count;
    int             someone_died;
    int             finished_eating;
    long            start_time;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
    pthread_mutex_t death_mutex;
    pthread_mutex_t meal_mutex;
    pthread_mutex_t finished_mutex;
};

void philo_eat(t_philo *philo);
int ft_atoi(const char *str);
int     parse_args(int argc, char **argv, t_rules *rules);
int     init_all(t_rules *rules, t_philo **philos);
long    get_time_ms(void);
void    smart_sleep(long time, t_rules *rules);
void    print_action(t_philo *philo, char *msg);
void    *philo_routine(void *arg);
void    *monitor_routine(void *arg);

#endif
