#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUFFER_SIZE 200
/****************************************************************/
int	ft_strlen(char *s)
{
	int	n = 0;
	while (s[n] != '\0')
		n++;
	return (n);
}
/****************************************************************/
static size_t	ft_strlcpy(char *dst, char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!src)
		return (0);
	if (size > 0)
	{
		while (i < size - 1 && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}
/****************************************************************/
char	*ft_strcat(char *s, char *append)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	while (append[j] != '\0')
	{
		s[i] = append[j];
		i++;
		j++;
	}
	s[i] = '\0';
	return (s);
}
/****************************************************************/
char *finding_new_line(char *buffer)
{
	size_t i = 0;
	char *data;
	
	while (buffer[i] != '\0' && buffer[i] != '\n' /*fd should be less than [OPEN_MAX]*/)
	{
		i++;
	}
	data = (char *)malloc((i * sizeof(char) + 1));
	i = 0;
	while (buffer[i] != '\0'/*fd should be less than [OPEN_MAX]*/)
	{
		if (buffer[i] == '\n')
		{
			/**
			 * since ft_strlcpy copy to the (size-1), so we dont copy '\n'
			 * to our new string.
			*/
			ft_strlcpy(data, buffer, i+1);
			data[i] = '\0';
			break;
		}
		i++;
	} 
	/**
	 * and the end you need to free the buffer to get ready to the next
	 * size of the data.
	*/
	return (data);
}
/****************************************************************/
void get_next_line(int fd, char **line)
{
/**
 * Variable section:
*/
	char buffer[BUFFER_SIZE];
	size_t read_res;
	int line_len;
	char *data;
	char *temp;
	
/****************************************************************/
/**
 * Here we are just seeing the result of the read() function
 * when we apply it to the file,
 * and also store the data that have been redden to the string (buffer).
*/
	read_res = read(fd, buffer, BUFFER_SIZE);
	/* buffer = (char *)malloc((BUFFER_SIZE * sizeof(char)) + 1);*/
	printf("\nThe result of read() is :%zu\n", read_res);
/****************************************************************/
	/**
	 * So the buffer will store the(BUFFER_SIZE) of data from the file 
	 * that have (fd) file descriptor.
	*/
	printf("The Buffer contain: \n%s\n", buffer);
	printf("The variable data contain: \n%s\n", finding_new_line(buffer));
	data = finding_new_line(buffer);
	line_len = ft_strlen(data);
	printf("The length of the string data is: \n%d\n", line_len);
	temp = (char *)malloc(line_len * sizeof(char) + 1);
	printf("The length of the variable (temp)[after malloc]: \n%d\n", ft_strlen(temp));
	ft_strcat(temp, data);
	printf("The variable temp [AFTER STRCAT()]contain:[after ft_strlcat()] \n%s\n", temp);
}
/****************************************************************/
int main()           
{
	int fd;
	static char **line;
	
	fd = open("bazz.txt", O_RDONLY);

	printf("fd is %d\n", fd);
	get_next_line(fd, line);
	close(fd);
	return (EXIT_SUCCESS);
}
/****************************************************************/
