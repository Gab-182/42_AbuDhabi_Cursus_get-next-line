/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@42ABUDHABI.AE>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 19:23:57 by gabdoush          #+#    #+#             */
/*   Updated: 2021/11/09 16:23:44 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 32
# define OPEN_MAX 256
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

char        *get_next_line(int fd);
size_t		ft_strlen(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strcpy(char *dst, const char *src);
char		*ft_strcat(char *s, const char *append);
char		*ft_strdup(const char *s1);
void        *ft_memset(void *dest, int c, size_t len);
void        *ft_memalloc(size_t size);

#endif
