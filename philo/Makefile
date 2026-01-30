.PHONY: all clean fclean re

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP -pthread
LIB = -pthread
SRC = ./philosophers.c \
	  ./error/error.c \
	  ./init/init.c \
	  ./utils/utils.c \
	  ./actions/action.c \
	  ./init/init_philo.c \
	  ./actions/monitor.c \
	  ./actions/utils_actions.c \

OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

NAME = philo

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $+ $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

-include $(DEP)

clean:
	rm -f $(OBJ) $(DEP)

fclean: clean
	rm -f $(NAME)

re: fclean all
