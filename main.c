#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main (int ac, char **av)
{
	int 	r = 0;
	char	*line = NULL;
	int		i = 0;

	if (ac == 1)
	{
		while ((r = get_next_line(STDIN_FILENO, &line)))
			printf("%d-%s\n", r, line);
	}
	else
	{
		
		while (++i < ac)
		{
			int fd = open(av[i], O_RDONLY);
			while ((r = get_next_line(fd, &line)) > 0)
				printf("%s", line);
			// printf("%d-%s\n", r, line);
			close(fd);
		}
	}
	
}