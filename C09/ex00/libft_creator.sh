#!/bin/bash

# Derleme işlemi için gcc kullanılacak
# -c flag'i ile object dosyaları oluşturulur.
gcc -Wall -Wextra -Werror -c ft_putchar.c ft_swap.c ft_putstr.c ft_strlen.c ft_strcmp.c

# Oluşturulan object dosyalarından libft.a kütüphanesi oluşturulur.
ar rcs libft.a ft_putchar.o ft_swap.o ft_putstr.o ft_strlen.o ft_strcmp.o

# Oluşturulan object dosyaları temizlenir.
rm -rf ft_putchar.o ft_swap.o ft_putstr.o ft_strlen.o ft_strcmp.o

echo "libft.a kütüphanesi başarıyla oluşturuldu."
