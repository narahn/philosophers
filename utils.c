#include "philo.h"

long get_time_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void smart_sleep(long time, t_rules *rules)
{
    long start = get_time_ms();
    while (get_time_ms() - start < time)
    {
        pthread_mutex_lock(&rules->death_mutex);
        if (rules->someone_died)
        {
            pthread_mutex_unlock(&rules->death_mutex);
            break;
        }
        pthread_mutex_unlock(&rules->death_mutex);
        usleep(500); // check frequently
    }
}


int ft_atoi(const char *str)
{
    int i = 0;
    int res = 0;

    while (str[i] >= '0' && str[i] <= '9')
    {
        res = res * 10 + (str[i] - '0');
        i++;
    }
    return res;
}
