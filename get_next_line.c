/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@42ABUDHABI.AE>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 22:43:43 by gabdoush          #+#    #+#             */
/*   Updated: 2021/11/10 13:22:10 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/* 
🍏🍏🍏🍏This functions has been checked 🍏🍏🍏🍏
Function to make free any string easier 
*/
static void	free_str(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
}

int		anlyze_errors(int fd, char *buffer)
{
	/* 
	 * #OPEN_MAX:  -----> is the maximum number of files that the operating
	 *                    system can store in the same session.

	 * #read(fd, buffer[fd], 0) -----> if nbyte is zero, the read() function may detect 
	 * 									   and return errors.
	 */
	if (! buffer || fd < 0 || fd >= OPEN_MAX || (read(fd, buffer, 0) < 0))
			return (0);
	return (1);
}

/* 
 * 🍏🍏🍏🍏This functions has been checked 🍏🍏🍏🍏
 * This function is to search for new line in the argument
 * (buffer) and then create a temporary variable, 
 * and allocate memory to it.
 * This temporary variable used to copy the text (until
 * we found new line), from the function argument (buffer).
 * or copy all the data from the buffer to it if we did not find a new line.
 */
static char	*search_new_line(char *buffer)
{
	char	*keep;
	int		i;

	i = 0;
	/* 
	 * step-1:
	 * - Checking that (basic text) is not a NULL string
	 */
	if (!buffer)
	    /* try to free buffer here while testing */
		return (NULL);
	/* 
	 * step-2:
	 * - Searching for new_line character. 
	 *   This step is just to help me to allocate the right amount
	 *   of memory to the temporary variable (temp).
	 */
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	/*
	 * NOTE:
	 * Here I wrote:
	 * (sizeof(char) * (i + 2));
	 * cause we need also to make some space to the text and ends with
	 * ['\n'  +  '\0'].
	 */
	keep = (char *) malloc(sizeof(char) * (i + 2));
	/* 
	 * step-3:
	 * Checking that (basic text) is not a NULL string
	 */
	if (!keep)
		return (NULL);
	/*
	 * step-4:
	 * Either If we found a new line or if we reached the end of the
	 * file whithout finding a new_line;
	 * We will copy all the characters from the first index of (buffer)
	 * to the temporary variable (temp). 
	*/
	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
	{
		keep[i] = buffer[i];
		i++;
	}
	/*
	 * step-5:
	 * # If the text ends with new_line:
	 * 	- Then we need to add new line char to the copied text in (temp).
	 * # If we reach the EOF without finding new_line:
	 * 	- don't do any thing.
	 */
	if (buffer[i] == '\n')
	{
		keep[i] = '\n';
		i++;
	}
	keep[i] = '\0';
	return (keep);
}

char	*reading_buffer(int fd, char *buffer)
{
	// int		bytes;
	// char 	*keep;
	// char	*buff;
	// int 	i;
	// i = 0;
	// bytes = read(fd, buff, BUFFER_SIZE);
	// while (bytes > 0)
	// {
    //     if (bytes == 0 || bytes < 0)
    //         break;
	// 	buff[bytes] = '\0';
	// 	if (buffer != NULL)
	// 	{
	// 		buffer = ft_strdup(buff);
	// 		keep = search_new_line(buffer);	
	// 		// buffer = ft_strjoin(temp, buffer);
	// 		/************** For Testing*********/
	// 		printf("%s\n", buffer);
	// 		// free_str(temp);
	// 		// search_new_line(buffer);
	// 	}
	// 	else
	// 	{
	// 		buffer = ft_strdup(buff);
	// 	}
    //     if (bytes == 0 || bytes < 0)
    //         break;
	// 	bytes = read(fd, buff, BUFFER_SIZE);
	// }
	// return (buffer);
/*===========================================================================*/
	char	*buff;
	int		bytes;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	/* We need to start the while loop, thats why the (bytes)
	 * should be more than (0).
	 * and also we are giving another value for the (bytes) variable
	 * inside the while loop.
	 */
	bytes = 1;
	/*
	 * In this step:
	 * 1- check if there is not new_line char .or.
	 * 	  the we are not at the end of the file;
	 * 	   {enter the while loop};  
	 */
	while (!ft_strchr(buffer, '\n') && bytes != 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
			free(buff);
			/* We don't write also the 
			 * buff = NULL; cause that will distroy the whole
			 * Blocks of memory for buff, and we need then to
			 * reallocate memory for (buff).
			 */
			return (NULL);
		
	}
}

char	*get_next_line(int fd)
{
	static char		*buffer;
	char			*line;
	
	/*
	 * Assign memory of size BUFFER_SIZE to the static variable (buffer).
	 */
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	/*
	 * check if there are any errors by checking the following:
	 * 1- check if the memory allocation for buffer is correct.
	 * 2- check the anlyze_error() function if it going to return (0).
	*/
	if (! buffer || anlyze_errors(fd, buffer) == 0)
		return (NULL);

	line = reading_buffer(fd, buffer);
	return (line);
}