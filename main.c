/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 05:43:51 by kmazier           #+#    #+#             */
/*   Updated: 2020/11/25 05:56:58 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main (int ac, char **av)
{
	char	*line = NULL;
	int		i = 0;

	while (++i < ac)
	{
		int fd = open(av[i], O_RDONLY);
		int r = 0;
		while ((r = get_next_line(fd, &line)) > 0)
		{
			printf("%d-%s\n", r, line);
			free(line);
			line = NULL;
		}
		printf("%d-%s\n", r, line);
			free(line);
			line = NULL;
	}
}