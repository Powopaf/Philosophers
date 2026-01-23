.PHONY: all clean fclean re

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP
LIB = 
SRC = 

OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

NAME = philo

all: $(NAME)

$(NAME): $(OBJ) libft/libft.a
	$(CC) -o $(NAME) $+ $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

-include $(DEP)

clean:
	rm -f $(OBJ) $(DEP)

fclean: clean
	rm -f $(NAME)

re: fclean all
