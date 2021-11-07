/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@42ABUDHABI.AE>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 22:43:43 by gabdoush          #+#    #+#             */
/*   Updated: 2021/11/08 02:35:13 by gabdoush         ###   ########.fr       */
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
int		search_new_line(char **basic_text, char **line)
{
	char	*temp;
	char 	*text;
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

/*************************__re-check here__**********************************/
	text = &temp[i];
	*text = '\0';
	*line = ft_strdup(*basic_text);
	*basic_text = ft_strdup(text + 1);
/****************************************************************************/
	free(temp);
	return (1);
}

int		reading_file(int fd, char *buf, char **basic_text, char **line)
{
	int		b;
	char	*temp;

	b = read(fd, buf, BUFF_SIZE);
	/* 
	 * While loop to reed the text from the file according to the
	 * BUFF_SIZE;
	 * So if BUFF_SIZE = 32, thats mean that each time the while loop will
	 * take 32 byte to read and deal with.
	 */
	while (b > 0)
	{
		/*
		 * Cause the read() function dont terminated the buf with '\0'
		 * That why we need to terminste manually.
		 */
		buf[b] = '\0';
		/*
		 * First case: 
		 * If the variable (*basic_text != NULL):
		 * 
		 * 1- copy the value of it to a temporary variavle (temp).
		 * 2- Make a new memory to (*basic_text) which will contain:
		 *    #(the previous value of (*basic_text) -----> temp)
		 *    and
		 *    #(new data that had been redden from read() at the first of the function).
		 * 3- Then free the temporary variable (temp) after fishing dealing with it.
		 */
		if (*basic_text != NULL)
		{
			temp = *basic_text;
			*basic_text = ft_strjoin(temp, buf);
			free(temp);
			temp = NULL;
		}
		/*
		 * Second case: 
		 * If the (*basic_text == NULL):
		 * Since *basic_text is NULL, then assign a data to it by make it hold the data
		 * that the variable (buf) has, after apply read function at the first.
		*/
		else
		{
			*basic_text = ft_strdup(buf);
		}
		/* If there is a new_line is the result of search_new_line(basic_text, line):
		 * Then break the function, and if there is not, do that agine.
		 */
		if (search_new_line(basic_text, line))
			break ;
	}
	/* 
	 *check if we did not reach the end of the file by checking the number of
	 * bytes that the function read() return each time.
	 */
	if (b > 0)
		return (1);
	return (b);
}

int		anlyze_errors(int fd, char **basic_text, char **line)
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
	static	char **line;
	char	*buffer;
	int		bytes;
	
	/*
	 * Assign memory of size BUFF_SIZE to the variable (buf).
	 */
	buffer = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	/*
	 * check if there are any errors by checking the following:
	 * 1- check if the memory allocation for buffer is correct.
	 * 2- check the anlyze_error() function if it going to return (0) or (1).
	*/
	
	if (! buffer || anlyze_errors(fd, basic_text, line) == 0)
		return (0);
	/**
	 * If there is no errors:
	 * 1- set the memory for the buffer.
	 * 2- reading_file(fd, buffer, basic_text, line); and assign its value of bytes
	 *    to the bytes variable.
	 * 3- Then free the memory of the buffer.
	*/
	buffer = ft_memset(buffer, '\0', BUFF_SIZE);
	bytes = reading_file(fd, buffer, basic_text, line);
	free(buffer);
	/* Moving the data to the line variable and free the memory of the variable basic_text. */
	*line = *basic_text;
	free_str(basic_text);
	return (*line);
}