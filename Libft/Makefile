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

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
