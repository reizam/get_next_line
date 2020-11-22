/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 17:33:43 by kmazier           #+#    #+#             */
/*   Updated: 2020/11/22 02:37:16 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


int		get_next_line_offset(t_list *lst)
{
	size_t	i;

	i = 0;
	if (!lst || !lst->content)
		return (0);
	while (lst->content[i])
		if (lst->content[i++] == '\n')
			return (i);
	return (0);
}

char	*get_line(size_t end, char *content)
{
	size_t	i;
	size_t	size;
	char	*result;

	i = 0;
	if (!(result = (char*)malloc(sizeof(char) * end)))
		return (NULL);
	while (i < end - 1)
		result[i++] = content[i];
	result[i] = 0;
	return (result);
}


int		get_next_line(int fd, char **line)
{
	static t_list 	*lst;
	t_list			*temp;
	ssize_t			i;
	char			buffer[BUFFER_SIZE + 1];

	if (!lst || !(temp = ft_lstget(lst, fd)))
		if(!(temp = ft_lstnew(lst, fd)))
		{
			lst = temp;
			return (-1);
		}
	while ((i = get_next_line_offset(temp)) == 0)
	{
		if ((i = read(fd, &buffer, BUFFER_SIZE)))
		{
			buffer[i] = 0;
			temp->content = ft_strjoin(temp->content, buffer);
		}
		if (i == 0 || i == -1)
			break ;
	}
	if (i == 0 || i == -1)
		return (i);
	if (*line)
		free(*line);
	*line = get_line(i, temp->content);
	temp->content = temp->content + i + 1;
	return (1);
}
