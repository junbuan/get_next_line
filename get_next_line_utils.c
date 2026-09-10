/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juho <juho@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 22:18:10 by juho              #+#    #+#             */
/*   Updated: 2026/09/09 23:43:40 by juho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*ptr;
	const char	*pt1;
	size_t		i;
	size_t		j;
	size_t		slen;

	if (!s)
		return (NULL);
	pt1 = s;
	slen = 0;
	while (*s++)
		slen++;
	if (start >= slen)
		len = 0;
	else if (len > slen - start)
		len = slen - start;
	ptr = malloc(len + 1);
	if (!ptr)
		return (NULL);
	i = start;
	j = 0;
	while (j < len)
		ptr[j++] = pt1[i++];
	return (ptr[j] = '\0', ptr);
}
char *ft_strjoin()

