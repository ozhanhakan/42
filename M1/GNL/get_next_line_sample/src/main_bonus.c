#include "../include/get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int fd1 = open("tests/three_paragraph.txt", O_RDONLY);
	int fd2 = open("tests/three_paragraph.txt", O_RDONLY);
	char *line1, *line2;
	int i = 1;

	while (i <= 4)
	{
		line1 = get_next_line(fd1);
		printf("fd1: %s", line1);
		free(line1);
		line2 = get_next_line(fd2);
		printf("fd2: %s", line2);
		free(line2);
		i++;
	}
	close(fd1);
	close(fd2);
	return 0;
}
