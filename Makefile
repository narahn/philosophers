NAME    = philo
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -I.

SRCS = \
	main.c \
	utils/ft_atoi.c \
	parsing.c \
	time_utils.c \
	philo_routine.c \
	initialize.c \
	monitor.c \
	start_simulation.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
