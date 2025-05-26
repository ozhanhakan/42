NAME 	= libft.a

CC 		= cc
CFLAGS 	= -Wall -Wextra -Werror

SRC_DIR	= .
SRCS	= $(wildcard $(SRC_DIR)/*.c)
OBJS	= $(SRCS:.c=.o)

AR		= ar rcs
RM		= rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

# Test binary oluşturur
test: all main.o
	$(CC) $(CFLAGS) main.o -L. -lft -o test

# main.o'yu üretir
main.o: main.c libft.h
	$(CC) $(CFLAGS) -c main.c -o main.o

clean:
	$(RM) $(OBJS)
# testi de siler.
fclean: clean
	$(RM) $(NAME) test

re: fclean all
