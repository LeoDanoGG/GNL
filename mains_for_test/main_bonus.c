/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legomez <legomez@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 15:21:27 by legomez           #+#    #+#             */
/*   Updated: 2026/10/19 15:45:32 by legomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main(int ac, char **av)
{
	int		fd;
	char	*line;
	int		i;

	if (ac < 2)
		return (1);
	for (i = 1; i < ac; i++)
	{
		fd = open(av[i], O_RDONLY);
		if (fd < 0)
		{
			printf("Error al abrir '%s'\n", av[i]);
				continue;
		}
		while ((line = get_next_line(fd)) != NULL)
		{
			printf("%s", line);
			free(line);
		}
		if (fd > 2)
			close(fd);
		printf("\n\n--=--=--= Fin de '%s' =--=--=--\n\n", av[i]);
	}
	return (0);
}
