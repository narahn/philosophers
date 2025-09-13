# include "philo.h"

int	ft_atoi(const char *str)
{
	int		i;
	int	sign;
	int	j;

	i = 0;
	sign = 1;
	j = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		j = j * 10 + (str[i] - '0');
		i++;
	}
	return (j * sign);
}
