/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 17:33:43 by kmazier           #+#    #+#             */
/*   Updated: 2020/11/23 23:02:21 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

int		parse_line(size_t end, char *content, char **line)
{
	size_t	i;
	char	*result;

	i = 0;
	if (!(result = (char*)malloc(sizeof(char) * (end + 1))))
		return (0);
	while (i < end)
	{
		result[i] = content[i];
		i++;
	}
	result[i] = 0;
	*line = result;
	return (1);
}

void	free_content(t_list **lst, ssize_t start)
{
	char	*result;
	size_t	i;

	i = ft_strlen((*lst)->content) - start;
	if (!(result = (char*)malloc(sizeof(char) * (i + 1))))
		return ;
	i = 0;
	while ((*lst)->content && (*lst)->content[start])
		result[i++] = (*lst)->content[start++];
	result[i] = 0;
	free((*lst)->content);
	(*lst)->content = result;
}

int		get_next_line(int fd, char **line)
{
	static t_list	*lst;
	t_list			*temp;
	ssize_t			i;
	ssize_t			j;
	char			buffer[BUFFER_SIZE + 1];

	if (!line || fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	if (!lst || !(temp = ft_lstget(lst, fd)))
		if (!(temp = ft_lstnew(&lst, fd)))
			return (-1);
	while ((i = read(fd, &buffer, BUFFER_SIZE)) >= 0)
	{
		if (i > 0)
			temp->content = ft_strjoin(temp->content, buffer, i);
		if (((j = get_next_line_offset(temp)) > 0) || i <= 0)
			break ;
	}
	if (i < 0)
		return (-1);
	i = ft_strlen(temp->content);
	parse_line(j == 0 && i >= 0 ? i : j - 1, temp->content, line);
	free_content(&temp, j == 0 && i >= 0 ? i : j);
	return (j == 0 ? 0 : 1);
}