#include "philo.h"

int main(int argc, char **argv)
{
    t_rules rules;

    if (parse_args(argc, argv, &rules))
        return (1);
    if (init_mutexes(&rules))
        return (1);
    rules.philos = malloc(sizeof(t_philo) * rules.nb_philo);
    if (!rules.philos)
    {
        cleanup(&rules);
        return (1);
    }
    init_philosophers(&rules, rules.philos);
    start_simulation(&rules);
    cleanup(&rules);
    return 0;
}
