/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@42ABUDHABI.AE>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 18:33:55 by gabdoush          #+#    #+#             */
/*   Updated: 2021/11/10 09:57:03 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// #include "get_next_line.c"
// #include "get_next_line_utils.c"
#include <stdio.h>
#include <fcntl.h>

int	main()
{
	int		fd;
	
	fd = open("buzz", O_RDONLY);
	printf("%s\n", get_next_line(fd));
	return (0);
}
