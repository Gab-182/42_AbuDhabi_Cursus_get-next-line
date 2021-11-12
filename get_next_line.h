#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
/************************************************************************/
# include <stdlib.h>
# include <unistd.h>
/************************************************************************/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif
/************************************************************************/
char	*get_next_line(int fd);
char	*ft_search_new_line(char *edited_buffer);
char	*ft_reading_buffer(int fd, char *edited_buffer);
char	*ft_get_next_text(char *edited_buffer);
int	ft_strlen(char *s);
char	*ft_strjoin(char *edited_buffer, char *buff);
char	*ft_strchr(char *s, int c);

#endif
/************************************************************************/