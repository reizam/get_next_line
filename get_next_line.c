/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 02:49:01 by kmazier           #+#    #+#             */
/*   Updated: 2020/11/25 03:22:04 by kmazier          ###   ########.fr       */
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
	char	*result;
	size_t 	i;

	i = 0;
	if (!(result = (char*)malloc(sizeof(char) * (end + 1))))
		return (0);
	while (i < end)
	{
		result[i] = str[i];
		i++;
	}
	result[i] = 0;
	*line = result;
	free(result);
	return (1);
}

int		update_buffer(ssize_t start, char **buffer)
{
	char	*result;
	ssize_t i;

	i = ft_strlen(*buffer) - start;
	if (!(result = (char*)malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (*buffer && *buffer[start])
		result[i++] = *buffer[start++];
	result[i] = 0;
	if (*buffer)
		free(*buffer);
	*buffer = result;
	free(result);
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
	while ((i = read(fd, &buffer, BUFFER_SIZE)) >= 0)
	{
		if (i > 0)
			gnl[fd] = ft_strjoin(&gnl[fd], &buffer);
		if ((j = get_next_line_offset(gnl[fd]) > 0) || i == 0)
			break ;
	}
	if (i < 0)
		return (-1);
	i = ft_strlen(gnl[fd]);
	if (!(get_and_copy_line(gnl[fd], line, j == 0 && i >= 0 ? i : j - 1)))
		return (-1);
	if (!(update_buffer(j == 0 && i >= 0 ? i : j, &gnl[fd])))
		return (-1);
	return (j == 0 ? 0 : 1);
}