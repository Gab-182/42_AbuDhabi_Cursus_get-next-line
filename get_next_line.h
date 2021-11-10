/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@42ABUDHABI.AE>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 19:23:57 by gabdoush          #+#    #+#             */
/*   Updated: 2021/11/10 22:36:51 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define OPEN_MAX 256
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

char        *get_next_line(int fd);
char	    *ft_search_new_line(char *buffer);
char	    *ft_reading_buffer(int fd, char *edited_buffer);
char		*ft_get_next_text(char *buffer);

size_t		ft_strlen(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);
char        *ft_strchr(const char *s, int c);

#endif
