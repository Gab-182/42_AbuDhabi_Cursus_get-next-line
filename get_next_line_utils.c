#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	n ;

	n = 0;
	while (s[n] != '\0')
	{
		n++;
	}
	return (n);
}

char	*ft_strjoin(char *edited_buffer, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!edited_buffer)
	{
		edited_buffer = (char *)malloc(1 * sizeof(char));
		edited_buffer[0] = '\0';
	}
	if (!edited_buffer || !buff)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(edited_buffer) + ft_strlen(buff)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (edited_buffer)
		while (edited_buffer[++i] != '\0')
			str[i] = edited_buffer[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_strlen(edited_buffer) + ft_strlen(buff)] = '\0';
	free(edited_buffer);
	return (str);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
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
char	*ft_search_new_line(char *buffer)
{
	char	*keep;
	int		i;

	i = 0;
	/* 
	 * step-1:
	 * - Checking that (basic text) is not a NULL string
	 */
	if (!buffer[i])
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
		keep[i] = buffer[i];
		i++;
	}
	keep[i] = '\0';
	return (keep);
}
/* 
 * 🍏🍏🍏🍏This functions has been checked 🍏🍏🍏🍏
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
	/* We need to start the while loop, thats why the (bytes)
	 * should be more than (0).
	 * and also we are giving another value for the (bytes) variable
	 * inside the while loop.
	 */
	bytes = 1;
	/*
	 * #In this step:
	 *     check if there is no new_line char .or.
	 * 	   if we are not at the end of the file;
	 * 	   {enter the while loop};  
	 */
	while ((!ft_strchr(edited_buffer, '\n') && (bytes != 0)))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			/* We don't write also the 
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

char	*ft_get_next_text(char *edited_buffer)
{
	int	i;
	int n;
	char *next_text;

	i = 0;
	n = 0;
	while (edited_buffer[i] != '\0' && edited_buffer[i] != '\n')
		i++;
	if (!edited_buffer)
	{
		free(edited_buffer);
		return (NULL);
	}
	next_text = (char *)malloc(sizeof(char) * (ft_strlen(edited_buffer) - i + 1));
	if (!next_text)
		return (NULL);
	while (edited_buffer[i])
	{
		next_text[n] = edited_buffer[i];
		i++;
		n++;
	}
	next_text[n] = '\0';
	free(edited_buffer);
	return (next_text);
}
