# Name of the output library
NAME	= libft.a

# Flags for the C compiler
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f
AR		= ar -crs
INC = libft.h

# sources files
SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c \
ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c \
ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

# object files
OBJS = $(SRCS:.c=.o)

# default target
all: $(NAME)

# making  archive from objects
$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

# Compile .c to .o
%.o: %.c $(INC)
	$(CC) $(CFLAGS) -I. -c $< -o $@

# cleaning rules
clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

# Recompile everything from scratch
re: fclean all

# Targets that are not actual files
.PHONY: all clean fclean re