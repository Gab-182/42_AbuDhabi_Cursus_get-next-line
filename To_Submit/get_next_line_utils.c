#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	n ;

	n = 0;
	if (!s)
		return (0);
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
	str = malloc(sizeof(char) * ((ft_strlen(edited_buffer)
					 + ft_strlen(buff)) + 1));
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
