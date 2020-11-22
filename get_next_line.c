/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 17:33:43 by kmazier           #+#    #+#             */
/*   Updated: 2020/11/22 23:54:44 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


int		get_next_line_offset(t_list *lst, ssize_t ret)
{
	size_t	i;

	i = 0;
	if (!lst || !lst->content)
		return (0);
	while (lst->content[i])
		if (lst->content[i++] == '\n')
			return (i);
	return (ret == 0 ? i : 0);
}

int		parse_line(size_t start, size_t end, char *content, char **line)
{
	size_t	i;
	char	*result;

	i = 0;
	if (!(result = (char*)malloc(sizeof(char) * ((end - start) + 1))))
		return (0);
	while (start < end)
		result[i++] = content[start++];
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
	while ((*lst)->content[start])
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
	
	if (!line || fd <= -1)
		return (-1);
	if (!lst || !(temp = ft_lstget(lst, fd)))
		if(!(temp = ft_lstnew(&lst, fd)))
			return (-1);
	i = 1;
	while ((j = get_next_line_offset(temp, i)) == 0 && i > 0)
		if ((i = read(fd, &buffer, BUFFER_SIZE)) > 0)
			temp->content = ft_strjoin(temp->content, buffer, i);
	if (i <= -1)
		return (-1);
	parse_line(0, i == 0 ? ft_strlen(temp->content) : j - 1, temp->content, line);
	free_content(&temp, j);
	return (i == 0 && j == 0 ? 0 : 1);
}
