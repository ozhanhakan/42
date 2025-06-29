/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 21:57:23 by hozhan            #+#    #+#             */
/*   Updated: 2025/06/29 10:44:20 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h> // malloc, free için
# include <unistd.h> // read için

// BUFFER_SIZE tanımlı değilse, varsayılan bir değer atanır.
// Derleyiciye -D BUFFER_SIZE=n parametresi ile bu değer değiştirilebilir. [cite: 37]
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define MAX_FD 1024

char	*get_next_line(int fd);

// Yardımcı Fonksiyonlar
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin_and_free(char *stash, char *buffer);

#endif