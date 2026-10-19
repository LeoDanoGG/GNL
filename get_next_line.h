/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legomez <legomez@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 09:44:36 by legomez           #+#    #+#             */
/*   Updated: 2026/10/19 15:22:20 by legomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/* Libs */
# include <unistd.h>
# include <stdlib.h>

/* GNL funtions */
char	*get_next_line(int fd);
char	*take_bytes(int fd);
char	*fill_stack(int fd, char *stack);
char	*build_line(char *stack);
char	*save_stack(char *stack);

/* GNL utils */
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_calloc(size_t num, size_t size);

/* BUFFER_SIZE */
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

#endif
