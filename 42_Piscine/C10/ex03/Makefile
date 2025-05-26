NAME = ft_hexdump
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRC = ft_hexdump.c
OBJ = $(SRC:.c=.o)
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

.PHONY: all clean fclean