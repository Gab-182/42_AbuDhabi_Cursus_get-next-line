/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@42ABUDHABI.AE>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 19:23:55 by gabdoush          #+#    #+#             */
/*   Updated: 2021/11/08 01:23:43 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*ft_strcat(char *s, const char *append)
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

char	*ft_strcpy(char *dst, const char *src)
{
	int	n;

	n = 0;
	while (src[n] != '\0')
	{
		dst[n] = src[n];
		n++;
	}
	dst[n] = '\0';
	return (dst);
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

void	*ft_memset(void *dest, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)dest)[i] = (unsigned char)c;
		i++;
	}
	return (dest);
}