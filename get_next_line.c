/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@42ABUDHABI.AE>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 22:43:43 by gabdoush          #+#    #+#             */
/*   Updated: 2021/11/07 02:09:11 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Function to make free any string easier */
void	free_str(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
}
/* 
 * Here the variable (line) is a static variable from the function g_n_l.
 *
 * So, basically here: we are coping making a temp string from the buffer,
 * and check that temp for any next_line char:
 * 	- if there one: 			
*/
char	**search_new_line__line(char **buffer, char **line)
{
	char	*temp;
	int		i;

	temp = *buffer;
	while (temp[i] != '\n' && temp[i] != '\0')
	{
		i++;
		if (temp[i] == '\0')
			return (0);
	}
	*line = *buffer;
	*buffer = ft_strdup("");
	free(temp);
	return (line);
}

char	reading_file_return__buffer(int fd, char *buf, char **buffer, char **line)
{
	int		b;
	char	*temp;

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
			free_str(temp);
		}
		else
		{
			/* If the (*buffer == NULL), make it duplicated from (buf) from the read() function.*/
			*buffer = ft_strdup(buf);
		}
		if (b < 0)
			return (0);
	}
	return (buffer);
}

void	anlyze_errors(int fd, char **buffer, char **line)
{
	/* 
	 * #OPEN_MAX:  -----> is the maximum number of files that the operating
	 *                    system can store in the same session.
	 * #buffer[fd]:-----> 
	 */
	if (! buffer || ! line || fd < 0 || fd > OPEN_MAX ||
		read(fd, buffer[fd], BUFFER_SIZE) < 0)

		{
			return (NULL);
		}
}

char	get_next_line(int fd)
{
	
}