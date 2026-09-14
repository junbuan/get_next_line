/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juho <juho@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 22:18:10 by juho              #+#    #+#             */
/*   Updated: 2026/09/14 15:06:49 by juho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*ptr;
	size_t		i;
	size_t		j;
	size_t		slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
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
		ptr[j++] = s[i++];
	return (ptr[j] = '\0', ptr);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	target;

	if (!s)
		return (NULL);
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

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = malloc(len1 + len2 + 1);
	if (!str)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (i < len1)
	{
		str[i] = s1[i];
		i++;
	}
	while (j < len2)
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	free(s1);
	return (str);
}
