NAME = get_next_line
NAME_BONUS = get_next_line_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror

MANDATORY = get_next_line.c get_next_line_utils.c
BONUS = get_next_line_bonus.c get_next_line_utils_bonus.c

all: $(NAME)

$(NAME): $(MANDATORY) main.c get_next_line.h
	$(CC) $(CFLAGS) $(MANDATORY) main.c -o $(NAME)

bonus: $(BONUS) main_bonus.c get_next_line_bonus.h
	$(CC) $(CFLAGS) $(BONUS) main_bonus.c -o $(NAME_BONUS)

clean:
	rm -f $(NAME) $(NAME_BONUS) *.o

fclean: clean

re: fclean all

.PHONY: all clean fclean re bonus
