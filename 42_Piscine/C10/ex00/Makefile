CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = ft_display_file
SRC = main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	# No object files to clean

fclean: clean
	rm -f $(TARGET)

.PHONY: all clean fclean