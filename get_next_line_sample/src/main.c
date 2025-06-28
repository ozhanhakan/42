/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 16:17:59 by hozhan            #+#    #+#             */
/*   Updated: 2025/06/28 16:23:48 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Basit bir test main fonksiyonu.
** tests/two_linthree_paragraph.txt dosyasını açar ve satır satır okur.
** Her satırı ekrana yazdırır ve bellek sızıntısı olmaması için free(line) çağırır.
*/
# include <stdio.h> 
#include "../include/get_next_line.h"
#include <fcntl.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("tests/three_paragraph.txt", O_RDONLY); // Test dosyasını aç
	while (1)
	{
		line = get_next_line(fd); // Satır oku
		printf("%s", line);      // Satırı ekrana yazdır
		if (line == NULL)
			break ;               // Satır yoksa döngüden çık
		free(line);             // Belleği serbest bırak
	}
	return (0);
}
