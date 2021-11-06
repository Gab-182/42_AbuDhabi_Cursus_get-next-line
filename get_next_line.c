/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@42ABUDHABI.AE>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 22:43:43 by gabdoush          #+#    #+#             */
/*   Updated: 2021/11/07 00:30:14 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Here the variable (line) is a static variable from the function gnl.*/

char		**search_new_line(char **buffer, char **line)
{
	char *temp;
	int i;
	
	temp = *buffer;
	while (temp[i] != '\n')
	{
		i++;
		if (temp[i] != '\0')
		{
			return (0);
		}
	}
	*line = *buffer;
	*buffer = ft_strdup("");
	free(temp);
	return (line);
}

char		reading_file(int fd, char *buf, char **buffer, char **line)
{
	int b;
	char *temp;
	
	b = read(fd, buf, BUFFER_SIZE);
	while (b > 0)
	{
		/* 
		 * Cause the read() function dont terminated the buf with '\0'
		 * That why we need to terminste manually.
		 */
		buf[b] = '\0';
		if (*buffer != NULL)
		{
			temp = *buffer;
			/* 
			 * When testing check the teo function, But i think you can not
			 * use ft_strcat, cause it cause you an error in the memory, But anuway check  that.
			 */
			*buffer = ft_strjoin(temp, buf);
			// *buffer = ft_strcat(temp, buf);
			free(temp);
			temp = NULL;
		}
		else
		{
			/* If the (*buffer == NULL), make it duplicated from (buf) from the read() function.*/
			*buffer = ft_strdup(buf);
		}
		if (b < 0)
			return (0);
	}
}