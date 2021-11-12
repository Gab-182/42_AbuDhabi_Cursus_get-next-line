#include "get_next_line.h"
/************************************************************************/
char	*get_next_line(int fd)
{
	static char		*edited_buffer;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	edited_buffer = ft_reading_buffer(fd, edited_buffer);
	if (!edited_buffer)
		return (NULL);
	line = ft_search_new_line(edited_buffer);
	edited_buffer = ft_get_next_text(edited_buffer);
	return (line);
}
/************************************************************************/