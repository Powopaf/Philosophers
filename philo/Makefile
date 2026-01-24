.PHONY: all clean fclean re

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP
LIB = 
SRC = ./philosophers.c \
	  ./error/error.c \
	  ./init/init.c \
	  ./utils/utils.c

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
	rm $(OBJ) $(DEP)

fclean: clean
	rm  $(NAME)

re: fclean all
