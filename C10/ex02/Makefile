NAME = ft_tail
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I includes

SRC = src/ft_tail.c src/ft_utils.c
OBJ = ft_tail.o ft_utils.o

all: $(NAME)

ft_tail.o: src/ft_tail.c includes/ft_tail.h
	$(CC) $(CFLAGS) -c src/ft_tail.c -o ft_tail.o

ft_utils.o: src/ft_utils.c includes/ft_tail.h
	$(CC) $(CFLAGS) -c src/ft_utils.c -o ft_utils.o

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f ft_tail.o ft_utils.o

fclean: clean
	rm -f $(NAME)

.PHONY: all clean fclean