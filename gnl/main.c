/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@42ABUDHABI.AE>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 18:33:55 by gabdoush          #+#    #+#             */
/*   Updated: 2021/11/07 11:07:48 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int		fd;
	int		fd1;
	char	*line;
	char	*line1;
	
	fd = open("teste", O_RDONLY);
	line = get_next_line(fd);
	printf("%s", line);
	return (0);
}
