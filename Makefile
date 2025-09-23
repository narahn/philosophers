NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=thread

SRCS = main.c \
       utils.c \
       parsing.c \
       initialize.c \
       action.c \
       philo_routine.c \
       monitor.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
