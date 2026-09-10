/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juho <juho@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 15:18:45 by juho              #+#    #+#             */
/*   Updated: 2026/09/09 19:25:19 by juho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE = 1024;
# endif
char *get_next_line(int fd);



# endif
