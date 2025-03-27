NAME		= do-op

SRC_DIR		= src
INC_DIR		= includes
OBJ_DIR		= obj

SRCS		= do_op.c operations.c helpers.c validation.c
OBJS		= $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I$(INC_DIR)

vpath %.c $(SRC_DIR)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "✅ Program derlendi!"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "🧹 Object dosyaları silindi!"

fclean: clean
	@rm -f $(NAME)
	@echo "🔥 Program temizlendi!"

re: fclean all

.PHONY: all clean fclean re