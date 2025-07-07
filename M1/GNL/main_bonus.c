#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int fd1 = open("test1.txt", O_RDONLY);
	int fd2 = open("test2.txt", O_RDONLY);
	char *line1;
	char *line2;

	while (1)
{
	line1 = get_next_line(fd1);
	line2 = get_next_line(fd2);
	if (!line1 && !line2)
		break;
	printf("fd1: %s", line1 ? line1 : "");
	printf("fd2: %s", line2 ? line2 : "");
	free(line1);
	free(line2);
}
	close(fd1);
	close(fd2);
	return 0;
}
