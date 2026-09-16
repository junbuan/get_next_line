/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juho <juho@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 22:18:10 by juho              #+#    #+#             */
/*   Updated: 2026/09/16 15:23:34 by juho             ###   ########.fr       */
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

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	target;

	target = (char)c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == target)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == target)
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	i;
	size_t	j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	newstr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (newstr == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		newstr[j++] = s1[i++];
	}
	i = 0;
	while (s2[i] != '\0')
	{
		newstr[j] = s2[i];
		i++;
		j++;
	}
	newstr[j] = '\0';
	return (newstr);
}
