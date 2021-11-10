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

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	n;

	s2 = (char *)malloc(ft_strlen(s1) + 1);
	n = 0;
	if (!s2)
	{
		return (NULL);
	}
	while (n < ft_strlen(s1))
	{
		s2[n] = ((char *)s1)[n];
		n++;
	}
	s2[n] = '\0';
	return (s2);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	new_str_len;
	char	*new_str;

	i = 0;
	j = 0;
	new_str_len = ft_strlen(s1) + ft_strlen(s2);
	new_str = (char *)malloc(new_str_len + 1);
	if (!s1 || !s2 || !new_str)
		return (0);
	while (s1[i] != '\0')
	{
		new_str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		new_str[i] = s2[j];
		i++;
		j++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*ft_strchr(const char *s, int c)
{
	int	n;

	n = ft_strlen(s);
	while (n >= 0)
	{
		if (*s == (char)c)
		{
			return ((char *)s);
		}
		s++;
		n--;
	}
	return (0);
}
