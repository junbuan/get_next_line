/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juho <juho@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 15:18:51 by juho              #+#    #+#             */
/*   Updated: 2026/09/14 15:06:43 by juho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char *stash)
{
	size_t	index;

	if (!stash || !stash[0])
		return (NULL);
	index = 0;
	while (stash[index] != '\0' && stash[index] != '\n')
		index++;
	return (ft_substr(stash, 0, index + (stash[index] == '\n')));
}

static char	*update_stash(char *stash)
{
	size_t	index;
	char	*new_stash;

	if (!stash)
		return (NULL);
	index = 0;
	while (stash[index] != '\0' && stash[index] != '\n')
		index++;
	if (stash[index] == '\0')
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_substr(stash, index + 1, ft_strlen(stash) - index - 1);
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		buffer[BUFFER_SIZE + 1];
	ssize_t		bytes_read;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(stash);
			stash = NULL;
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		stash = ft_strjoin(stash, buffer);
		if (!stash)
			return (NULL);
	}
	if (!stash || !stash[0])
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = extract_line(stash);
	if (!line)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = update_stash(stash);
	return (line);
}
