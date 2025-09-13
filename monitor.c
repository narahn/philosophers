# include "philo.h"

#include "philo.h"

void *monitor(void *arg)
{
    t_rules *rules = (t_rules *)arg;
    int i;
    long now;

    while (!rules->someone_died)
    {
        i = 0;
        while (i < rules->nb_philo)
        {
            now = current_time_ms();
            if (now - rules->philos[i].last_meal > rules->time_to_die)
            {
                pthread_mutex_lock(&rules->print_mutex);
                printf("%ld %d died\n", now - rules->start_time, rules->philos[i].id);
                rules->someone_died = 1;
                pthread_mutex_unlock(&rules->print_mutex);
                return NULL;
            }
            i++;
        }
        usleep(1000); // reduce CPU usage
    }
    return NULL;
}
