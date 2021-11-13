#include "get_next_line.h"
# include <stdio.h>

/************************************************************************/
int	ft_strlen(char *s)
{
	int	n ;

	n = 0;
	if (!s) 
		return (0);
	while (s[n] != '\0')
	{
		n++;
	}
	return (n);
}
/************************************************************************/
char	*ft_strchr(char *s, int c)
{
	int	n;

	if (!s)
		return (0);
	n = ft_strlen(s);
	while (n >= 0)
	{
		if (*s == (char)c)
		{
			return (s);
		}
		s++;
		n--;
	}
	return (0);
}
/************************************************************************/
char	*ft_strjoin(char *left_str, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!left_str)
	{
		left_str = (char *)malloc(1 * sizeof(char));
		left_str[0] = '\0';
	}
	if (!left_str || !buff)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(left_str) + ft_strlen(buff)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (left_str)
		while (left_str[++i] != '\0')
			str[i] = left_str[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_strlen(left_str) + ft_strlen(buff)] = '\0';
	free(left_str);
	return (str);
}
/************************************************************************/
/* 
 * 🍏This functions has been checked 🍏
 * This function is to read from the read() buffer;
 * if there is no error and no new_line, then it will
 * give join read() buffer to the (edited_buffer) and return it.
 */
char	*ft_reading_buffer(int fd, char *edited_buffer)
{
	char	*buffer;
	int		bytes;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	/* 
	 * We need to start the while loop, thats why the (bytes)
	 * should be more than (0).
	 * and also we are giving another value for the (bytes) variable
	 * inside the while loop.
	 */
	bytes = 1;
	/*
	 * #In this step:
	 *    #check if there is no new_line char .or.
	 * 	   if we are not at the end of the file;
	 ***************************************************************
	 * 	  #ft_strchr() will return NULL if the char did not found in
	 * 	   the string.
	 */
	while ((ft_strchr(edited_buffer, '\n') == NULL && (bytes != 0)))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		/* 
		 * If bytes == -1
		 * That is mean there was an error during the reading of the file.
		 */
		if (bytes == -1)
		{
			free(buffer);
			/* 
			 * We don't write also the 
			 * buff = NULL; cause that will distroy the whole
			 * Blocks of memory for buff, and we need then to
			 * reallocate memory for (buff).
			 */
			return (NULL);
		}
		/* 
		 * Terminate the read() buffer, cause it don't terminate it
		 * by it self.
		 */
		buffer[bytes] = '\0';
		edited_buffer = ft_strjoin(edited_buffer, buffer);
	}
	free(buffer);
	return (edited_buffer);
}
/************************************************************************/
/* 
 * 🍏This functions has been checked 🍏
 * This function is to search for new line in the argument
 * (buffer) and then create a temporary variable, 
 * and allocate memory to it.
 * This temporary variable used to copy the text (until
 * we found new line), from the function argument (buffer).
 * or copy all the data from the buffer to it if we did not find a new line.
 */
char	*ft_search_new_line(char *edited_buffer)
{
	char	*line;
	int		i;

	i = 0;
	/*
	 * step-1:
	 * Basically we are checking here if the file is empty. 
	 */
	if (!edited_buffer[i])
		return (NULL);
	/* 
	 * step-2:
	 * - Searching for new_line character. 
	 *   This step is just to help me to allocate the right amount
	 *   of memory to the temporary variable (temp).
	 */
	while (edited_buffer[i] != '\n' && edited_buffer[i] != '\0')
		i++;
	/*
	 * NOTE:
	 * Here I wrote:
	 * (sizeof(char) * (i + 2));
	 * cause we need also to make some space to the text and ends with
	 * ['\n'  +  '\0'].
	 */
	line = (char *) malloc(sizeof(char) * (i + 2));
	/* 
	 * step-3:
	 * Checking that (basic text) is not a NULL string
	 */
	if (!line)
		return (NULL);
	/*
	 * step-4:
	 * Either If we found a new line or if we reached the end of the
	 * file whithout finding a new_line;
	 * We will copy all the characters from the first index of (buffer)
	 * to the temporary variable (temp). 
	*/
	i = 0;
	while (edited_buffer[i] && edited_buffer[i] != '\n')
	{
		line[i] = edited_buffer[i];
		i++;
	}
	/*
	 * step-5:
	 * # If the text ends with new_line:
	 * 	- Then we need to add new line char to the copied text in (temp).
	 * # If we reach the EOF without finding new_line:
	 * 	- don't do any thing.
	 */
	if (edited_buffer[i] == '\n')
	{
		line[i] = edited_buffer[i];
		/* Then increasing (i) for the null */
		i++;
	}
	line[i] = '\0';
	return (line);
}
/************************************************************************/
/*
 * 🍏This functions has been checked 🍏
 * This function Basically to store the next line in 
 * memory of the static variable, so it will be ready when
 * call the function get_next_line() agine. and then the 
 * get_next_line() function will return the next line and so on 
 * until we reach the EOF.
 */
char	*ft_get_next_text(char *edited_buffer)
{
	int		i;
	int 	n;
	char 	*next_text;

	i = 0;
	n = 0;
	while (edited_buffer[i] && edited_buffer[i] != '\n')
		i++;
	/*
	 * This while loop will help me to reach the (line) memory so i can
	 * store the rest of (edited_buffer) in the new memory (next_text).
	 */
	if (!edited_buffer[i])
	{
		free(edited_buffer);
		return (NULL);
	}
	/*
	 * (i) here is basically the length of the variable (line)
	 */
	next_text = (char *)malloc(sizeof(char) * (ft_strlen(edited_buffer) - i + 1));
	if (!next_text)
		return (NULL);
	/*
	 * i++ -----> To pass the new_line that we included
	 * in the (line) variable and move to the next char in (edited_buffer).
	 */
	i++;
	/*
	 * Using the while loop to copy the data from (edited_buffer)
	 * to the (next text), 
	 */
	while (edited_buffer[i])
	{
		next_text[n] = edited_buffer[i];
		n++;
		i++;
	}
	/*
	 * Terminate (next_text) with '\0'.
	 * Then free the previous memory data of (edited_buffer)
	 * To prepare it to store (next_text).
	*/
	next_text[n] = '\0';
	free(edited_buffer);
	return (next_text);
}
/************************************************************************/