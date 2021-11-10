#include "get_next_line.h"

/* 
 *🍏🍏🍏🍏This functions has been checked 🍏🍏🍏🍏
 *Function to check the errors in the last step.
*/
int		ft_anlyze_errors(int fd, char *buffer)
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
static char	*ft_search_new_line(char *buffer)
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

/* 
 * 🍏🍏🍏🍏This functions has been checked 🍏🍏🍏🍏
 * This function is to read from the read() buffer;
 * if there is no error and no new_line, then it will
 * give join read() buffer to the (edited_buffer) and return it.
 */
static char	*ft_reading_buffer(int fd, char *edited_buffer)
{
	char	*buffer;
	int		bytes;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
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
	while ((ft_strchr(edited_buffer, '\n') == NULL) && (bytes != 0))
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

static char		*ft_get_next_text(char *buffer)
{
	int	i;
	int n;
	char *next_text;

	i = 0;
	n = 0;
	if (!buffer)
	{
		free(buffer);
		return (NULL);
	}
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	next_text = (char *)malloc(sizeof(char) * (ft_strlen(buffer) - i + 1));
	if (!next_text)
	{
		free(next_text);
		return (NULL);
	}
	while (buffer[i] != '\0')
	{
		next_text[n] = buffer[i];
		i++;
		n++;
	}
	next_text[n] = '\0';
	free(buffer);
	return (next_text);
}

char	*get_next_line(int fd)
{
	static char		*buffer;
	char			*line;

	if (! buffer || ft_anlyze_errors(fd, buffer) == 0)
		return (NULL);
	buffer = ft_reading_buffer(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_search_new_line(buffer);
	buffer = ft_get_next_text(buffer);
	return (line);
}