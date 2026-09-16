/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juho <juho@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 15:18:51 by juho              #+#    #+#             */
/*   Updated: 2026/09/16 21:51:48 by juho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
	static char	*saved;
	char		buf[BUFFER_SIZE + 1];
	ssize_t		bytes_read;
	char		*line;
	char		*temp;
	char		*nl;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (ft_strchr(saved, '\n'))
			break;
		bytes_read = read (fd, buf, BUFFER_SIZE);
		temp = saved;
		if (bytes_read <= 0)
			break;
		else if (ft_strchr(temp,'\n'))
			break;
		buf[bytes_read] = '\0';
		saved = ft_strjoin(buf,temp);
		free (temp);
	}
	if (bytes_read == -1)
		return (NULL);
	if (!saved)
		return (NULL);
	nl = ft_strchr(saved, '\n');
	if (nl == NULL)
	{
	line = saved;      // the whole leftover IS the final line — no \n to strip
	saved = NULL;       // nothing left for next time
	return (line);       // note: no free() here — we're handing "line" ownership to the caller
	}
	line = ft_substr(saved, 0, nl - saved);
	temp = saved;
	free(saved);
	return (line);
}
