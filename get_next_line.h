/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 17:34:36 by kmazier           #+#    #+#             */
/*   Updated: 2020/11/22 23:47:31 by kmazier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 4096

typedef struct	s_list
{
	int				fd;
	char			*content;
	struct s_list	*next;
}				t_list;

t_list	*ft_lstnew(t_list **begin, int fd);
t_list	*ft_lstget(t_list *begin, int fd);
int		get_next_line(int fd, char **line);
char	*ft_strjoin(char *s1, char *s2, ssize_t s2_size);
size_t	ft_strlen(const char *s);

#endif
