#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_philo t_philo;
typedef struct s_rules t_rules;

struct s_rules
{
    int nb_philo;              // number of philosophers
    int time_to_die;           // time (ms) before a philo dies without eating
    int time_to_eat;           // time (ms) a philo spends eating
    int time_to_sleep;         // time (ms) a philo spends sleeping
    int must_eat_count;        // how many times each philo must eat (optional)
    int someone_died;        // flag to stop simulation
    int finished_eating;
    pthread_mutex_t finished_mutex;
    pthread_mutex_t print_mutex; // lock for printing messages
    pthread_mutex_t *forks;    // array of forks
    long start_time;
    t_philo *philos;           // array of philosophers
};

struct s_philo
{
    int id;                    // philosopher number
    int meals_eaten;
    long last_meal;
    pthread_t thread;          // the thread for this philosopher
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_rules *rules;            // pointer to the rules
};




// utils.c
int ft_atoi(const char *str);

//parsing.c
int parse_args(int argc, char **argv, t_rules *rules);

//time_utils.c
long current_time_ms(void);

//philo_routine.c
void *philo_routine(void *arg);

//initialize.c
void init_philosophers(t_rules *rules, t_philo *philos);
int init_mutexes(t_rules *rules);
void destroy_mutexes(t_rules *rules);
void free_philos(t_philo *philos);

// monitor.c
void *monitor(void *arg);

//start_simulation.c
void start_simulation(t_rules *rules);
void cleanup(t_rules *rules);

#endif

