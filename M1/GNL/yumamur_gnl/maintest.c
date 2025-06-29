#include <fcntl.h>
#include <stdio.h>
//#include "get_next_line.h"
#include "get_next_line_bonus.h"

#define TEST_FILE ~/francinette/tests/get_next_line/gnlTester/files

int	main(void)
{
	char *tmp;

	int fd1 = open("/Users/yumamur/francinette/tests/get_next_line/fsoares/read_error.txt", O_RDONLY);
	int	fd2 = open("/Users/yumamur/francinette/tests/get_next_line/fsoares/lines_around_10.txt", O_RDONLY);

	tmp = get_next_line(fd1);
	printf("\nmain\tfd1\t%s\n", tmp);
	free(tmp);
	tmp = get_next_line(fd2);
	printf("\nmain\tfd2\t%s\n", tmp);
	free(tmp);
	tmp = get_next_line(fd1);
	printf("\nmain\tfd1\t%s\n", tmp);
	free(tmp);
	tmp = get_next_line(fd2);
	printf("\nmain\tfd2\t%s\n", tmp);
	free(tmp);
	tmp = get_next_line(fd1);
	free(tmp);
	tmp = get_next_line(fd1);
	free(tmp);
	tmp = get_next_line(fd1);
	free(tmp);
	tmp = get_next_line(fd1);
	free(tmp);
	tmp = get_next_line(fd1);
	printf("\nmain\tfd1\t%s\n", tmp);
	free(tmp);
	tmp = get_next_line(fd2);
	printf("\nmain\tfd2\t%s\n", tmp);
	free(tmp);
}
