/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 02:49:01 by kmazier           #+#    #+#             */
/*   Updated: 2020/11/25 17:26:49 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	get_next_line_offset(char *str)
{
	ssize_t i;

	i = 0;
	while (str && str[i])
		if (str[i++] == '\n')
			return (i);
	return (0);
}

int		get_and_copy_line(char *str, char **line, ssize_t end)
{
	char		*result;
	ssize_t		i;

	i = 0;
	if (!(result = (char*)malloc(sizeof(char) * (end + 1))))
	{
		if (str)
			free(str);
		return (0);
	}
	while (i < end)
	{
		result[i] = str[i];
		i++;
	}
	result[i] = 0;
	*line = result;
	return (1);
}

int		get_and_free_str(ssize_t start, char **gnl, int fd)
{
	char	*result;
	ssize_t	i;

	i = ft_strlen(gnl[fd]) - start;
	if (i <= 0)
	{
		if (gnl[fd])
			free(gnl[fd]);
		gnl[fd] = 0;
		return (1);
	}
	if (!(result = (char*)malloc(sizeof(char) * (i + 1))))
	{
		if (gnl[fd])
			free(gnl[fd]);
		return (0);
	}
	i = 0;
	while (gnl[fd] && gnl[fd][start])
		result[i++] = gnl[fd][start++];
	result[i] = 0;
	if (gnl[fd])
		free(gnl[fd]);
	gnl[fd] = result;
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char	*gnl[OPEN_MAX];
	char		buffer[BUFFER_SIZE + 1];
	ssize_t		i;
	ssize_t		j;

	if (!line || fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	while ((i = read(fd, buffer, BUFFER_SIZE)) >= 0)
	{
		if (i > 0)
			gnl[fd] = ft_strjoin(gnl[fd], buffer, i);
		if (((j = get_next_line_offset(gnl[fd])) > 0) || i == 0)
			break ;
	}
	if (i < 0)
		return (-1);
	i = ft_strlen(gnl[fd]);
	if (!(get_and_copy_line(gnl[fd], line, j == 0 && i >= 0 ? i : j - 1)))
		return (-1);
	if (!(get_and_free_str(j == 0 && i >= 0 ? i : j, gnl, fd)))
		return (-1);
	return (j == 0 ? 0 : 1);
}
