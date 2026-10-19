/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legomez <legomez@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 15:21:29 by legomez           #+#    #+#             */
/*   Updated: 2026/10/19 15:36:47 by legomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main(int ac, char **av)
{
	int		fd;
	char	*line;
	int		line_count;

	line_count = 1;
	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd < 0)
			return (1);
		printf("Leyendo '%s'\n", av[1]);
	}
	else
		return (1);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	if (fd > 2)
		close(fd);
	return (0);
}
