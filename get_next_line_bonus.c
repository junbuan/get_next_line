/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juho <juho@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 18:39:10 by juho              #+#    #+#             */
/*   Updated: 2026/09/09 18:39:16 by juho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_to_saved(int fd, char *saved)
{
	char	*buf;
	char	*temp;
	ssize_t	bytes_read;

	buf = malloc((size_t)BUFFER_SIZE + 1);
	if (!buf)
		return (free(saved), NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(saved, '\n'))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buf), free(saved), NULL);
		buf[bytes_read] = '\0';
		temp = saved;
		saved = ft_strjoin(temp, buf);
		free(temp);
		if (!saved)
			return (free(buf), NULL);
	}
	free(buf);
	return (saved);
}

static char	*extract_line(char *saved)
{
	char	*nl;

	if (!saved || !*saved)
		return (NULL);
	nl = ft_strchr(saved, '\n');
	if (!nl)
		return (ft_substr(saved, 0, ft_strlen(saved)));
	return (ft_substr(saved, 0, nl - saved + 1));
}

static char	*trim_saved(char *saved)
{
	char	*nl;
	char	*rest;

	nl = ft_strchr(saved, '\n');
	if (!nl || !nl[1])
		return (free(saved), NULL);
	rest = ft_substr(nl + 1, 0, ft_strlen(nl + 1));
	free(saved);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*saved[OPEN_MAX];
	char		*line;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	saved[fd] = read_to_saved(fd, saved[fd]);
	line = extract_line(saved[fd]);
	saved[fd] = trim_saved(saved[fd]);
	return (line);
}
