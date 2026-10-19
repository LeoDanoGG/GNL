/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legomez <legomez@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 09:49:55 by legomez           #+#    #+#             */
/*   Updated: 2026/10/19 15:19:54 by legomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*take_bytes(int fd)
{
	int		bytes;
	char	*buffer;

	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (NULL);
	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes <= 0)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

char	*build_line(char *stack)
{
	char	*ptr;
	size_t	len;

	ptr = ft_strchr(stack, '\n');
	if (ptr)
		len = (ptr - stack) + 1;
	else
		len = ft_strlen(stack);
	return (ft_substr(stack, 0, len));
}

char	*save_stack(char *stack)
{
	char	*new_stack;
	char	*ptr;

	ptr = ft_strchr(stack, '\n');
	if (!ptr)
	{
		free(stack);
		return (NULL);
	}
	new_stack = ft_substr((ptr + 1), 0, ft_strlen(ptr) + 1);
	free(stack);
	return (new_stack);
}

char	*fill_stack(int fd, char *stack)
{
	char	*buff;
	char	*tmp;

	while (!ft_strchr(stack, '\n'))
	{
		buff = take_bytes(fd);
		if (!buff)
			break ;
		tmp = ft_strjoin(stack, buff);
		free(stack);
		free(buff);
		stack = tmp;
		if (!stack)
			return (NULL);
	}
	return (stack);
}

char	*get_next_line(int fd)
{
	static char	*stack[FDS];
	char		*line;

	if (fd < 0 || (FDS < 0 || FDS > 1024) || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stack[fd])
	{
		stack[fd] = ft_calloc(1, sizeof(char *));
		if (!stack[fd])
			return (NULL);
	}
	stack[fd] = fill_stack(fd, stack[fd]);
	if (!stack[fd] || !stack[fd][0])
	{
		free(stack[fd]);
		stack[fd] = NULL;
		return (NULL);
	}
	line = build_line(stack[fd]);
	stack[fd] = save_stack(stack[fd]);
	return (line);
}
