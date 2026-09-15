/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juho <juho@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 15:18:51 by juho              #+#    #+#             */
/*   Updated: 2026/09/15 21:24:07 by juho             ###   ########.fr       */
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

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while ((!ft_strchr(saved,'\n')) || bytes_read <= 0)
	{
		bytes_read = read (fd, buf, BUFFER_SIZE);
		temp = saved;
		saved = ft_strjoin(buf,temp);
		free (temp);
	}
	if (bytes_read == -1)
		return (NULL);
	if (!saved)
		return (NULL);
	line = ft_substr(saved,0,ft_strchr(saved,'\n'));
	free(saved);
	return (line);

	 // 1. loop: read into buf, join onto saved, until \n found or read() <= 0
    // 2. if error (-1) -> clean up, return NULL
    // 3. if saved is empty/NULL -> return NULL
    // 4. split saved into line (to return) and new leftover
    // 5. free old saved, update saved = new leftover, return line
}
