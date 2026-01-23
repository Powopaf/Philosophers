.PHONY: all clean fclean re

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIB = 
SRC = 

OBJ = $(SRC:.c=.o)

NAME = p

all: $(NAME)

$(NAME): $(OBJ) libft/libft.a
	$(CC) -o $(NAME) $+ $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
