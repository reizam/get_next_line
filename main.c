
#include "get_next_line.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int ac, char **av)
{
	char	*line = NULL;
	int fd = open(av[1], O_RDONLY);
	int fd2 = open(av[2], O_RDONLY);
	printf("FD:%d\n", fd);
	get_next_line(fd, &line);
	printf("%s\n", line);
	get_next_line(fd2, &line);
	printf("%s\n", line);
	get_next_line(fd, &line);
	printf("%s\n", line);
	get_next_line(fd2, &line);
	printf("%s\n", line);
}