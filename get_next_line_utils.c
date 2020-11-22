/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 17:34:07 by kmazier           #+#    #+#             */
/*   Updated: 2020/11/22 02:35:17 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char			*result;
	size_t			i;
	size_t			j;

	i = (s1 == NULL ? 0 : ft_strlen((char*)s1))
	+ (s2 == NULL ? 0 : ft_strlen((char*)s2));
	if (!(result = (char*)malloc((i + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[j])
		result[i++] = s1[j++];
	j = 0;
	while (s2 && s2[j])
		result[i++] = s2[j++];
	result[i] = 0;
	if (s1)
		free(s1);
	return (result);
}


void	ft_lstclear(t_list **lst)
{
	t_list *next;

	if (lst == NULL || *lst == NULL)
		return ;
	while (*lst)
	{
		next = (*lst)->next;
		free((*lst)->content);
		free((*lst));
		(*lst) = NULL;
		(*lst) = next;
	}
	lst = NULL;
}

t_list	*ft_lstget(t_list *begin, int fd)
{
	if (begin == NULL)
		return (NULL);
	while (begin)
	{
		if (begin->fd == fd)
			return (begin);
		begin = begin->next;
	}
	return (NULL);
}

t_list	*ft_lstnew(t_list *next, int fd)
{
	t_list *lst;

	if (!(lst = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	lst->fd = fd;
	lst->content = NULL;
	if (next)
		lst->next = next;
	else
		lst->next = NULL;
	return (lst);
}
