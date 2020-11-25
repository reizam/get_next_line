/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmazier <kmazier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 02:52:23 by kmazier           #+#    #+#             */
/*   Updated: 2020/11/25 03:20:02 by kmazier          ###   ########.fr       */
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

char	*ft_strjoin(char **s1, char **s2)
{
	char			*result;
	size_t			i;
	size_t			j;

	i = (*s1 == NULL ? 0 : ft_strlen(*s1))
	+ (*s2 == NULL ? 0 : ft_strlen(*s2));
	if (!(result = (char*)malloc((i + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	j = 0;
	while (*s1 && *s1[j])
		result[i++] = *s1[j++];
	j = 0;
	while (*s2 && *s2[j])
		result[i++] = *s2[j++];
	result[i] = 0;
	if (*s1)
		free(*s1);
	if (*s2)
		free(*s2);
	return (result);
}
