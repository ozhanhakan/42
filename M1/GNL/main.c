#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

/* int main(void)
{
	int fd = open("test.txt", O_RDONLY);
	char *line = NULL;

	line = get_next_line(0);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return 0;
} */
int main(void)
{
	int fd = open("test.txt", O_RDONLY);
	char *line;
	printf("Buffer Size: %d\n", BUFFER_SIZE);
	while ((line = get_next_line(fd)))
	{
		printf("line: [%s]\n", line);
		free(line);
	}
	close(fd);
	return (0);
}
