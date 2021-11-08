/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@42ABUDHABI.AE>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 22:43:43 by gabdoush          #+#    #+#             */
/*   Updated: 2021/11/08 00:09:09 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Function to make free any string easier */
void	free_str(char **str)
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
 * So, basically here: we are coping making a temp string from the (basic_text),
 * and check that temp for any next_line char:
 * 	- if there one: 			
*/
int		search_new_line(char **basic_text, char *line)
{
	char	*temp;
	int		i;

	i = 0;
	temp = *basic_text;
	while (temp[i] != '\n')
	{
		i++;
		if (temp[i] == '\0')
			return (0);
	}
	/* If we fined new line, do the rest of the code and return (1)*/
	line = ft_strdup(*basic_text);
	*basic_text = ft_strdup("");
	free(temp);
	return (1);
}

int		reading_file(int fd, char *buf, char **basic_text, char *line)
{
	int		b;
	char	*temp;

	b = read(fd, buf, BUFF_SIZE);
	while (b > 0)
	{
		/*
		 * Cause the read() function dont terminated the buf with '\0'
		 * That why we need to terminste manually.
		 */
		buf[b] = '\0';
		if (*basic_text != NULL)
		{
			temp = *basic_text;
			/*
			 * When testing check the teo function, But i think you can not
			 * use ft_strcat, cause it cause you an error in the memory, But anuway check  that.
			 */
			*basic_text = ft_strjoin(temp, buf);
			// *basic_text = ft_strcat(temp, buf);
			free_str(&temp);
		}
		else
		{
			/* If the (*basic_text == NULL), make it duplicated from (buf) from the read() function.*/
			*basic_text = ft_strdup(buf);
		}
		if (search_new_line(basic_text, line))
			break ;
		if (b > 0)
			return (1);
	}
	return (b);
}

int		anlyze_errors(int fd, char **basic_text, char *line)
{
	/* 
	 * #OPEN_MAX:  -----> is the maximum number of files that the operating
	 *                    system can store in the same session.

	 * #read(fd, basic_text[fd], 0) -----> if nbyte is zero, the read() function may detect 
	 * 									   and return errors.
	 */
	if (! basic_text || ! line || fd < 0 || fd >= OPEN_MAX || (read(fd, basic_text, 0) < 0))
		{
			return (0);
		}
	return (1);
}

char	*get_next_line(int fd)
{
	static	char **basic_text;
	static	char *line;
	char	*buffer;
	int		bytes;
	
	buffer = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	if (anlyze_errors(fd, basic_text, line) == 0 || ! buffer)
		return (0);
	/*
	 * Important..................................................
	 * While testing, try to replace the next two lines, with
	 * buffer = (char *)ft_calloc(sizeof(char) * (BUFF_SIZE + 1));
	 */
	// buffer = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	buffer = ft_memset(buffer, '\0', BUFF_SIZE);
	/*.............................................................*/
	/* coping the required data from buffer to basic_text */
	bytes = reading_file(fd, buffer, basic_text, line);
	free(buffer);
	
    if (bytes != 0 || basic_text == NULL)
    {
        if (!bytes && line)
            *line = '\0';
    }
	
	/* Moving the data to the line variabe and free the memory. */
	line = *basic_text;
	free_str(basic_text);
	return (line);
}

