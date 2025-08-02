NAME = philo
FUN = main.c routine.c pars.c start_philo.c actions_monitor.c help_start.c
OBJ = $(FUN:.c=.o)
CC = cc -g3
CFLAGS = -Wall -Wextra -Werror 

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(NAME)

clean:
	rm -rf $(OBJ)
fclean: clean
	rm -rf $(NAME)
re: fclean all

.PHONY: clean
