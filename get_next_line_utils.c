/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legomez <legomez@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 09:51:01 by legomez           #+#    #+#             */
/*   Updated: 2026/10/19 14:41:14 by legomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t num, size_t size)
{
	void			*call;
	unsigned char	*zero;
	size_t			len;

	zero = NULL;
	call = malloc(num * size);
	if (call != NULL)
	{
		zero = call;
		len = (num * size);
		while (len-- > 0)
			zero[len] = 0;
	}
	return (zero);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*c;
	size_t	l1;
	size_t	l2;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	c = ft_calloc((l1 + l2 + 1), sizeof(char));
	if (!c)
		return (NULL);
	while (i < l1)
	{
		c[i] = s1[i];
		i++;
	}
	while (i < (l1 + l2))
	{
		c[i] = s2[i - l1];
		i++;
	}
	return (c);
}

char	*ft_strchr(const char *s, int c)
{
	char	*chr;

	chr = NULL;
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char) c)
			return ((char *) s);
		s++;
	}
	if ((char) c == '\0')
		return ((char *) s);
	return (chr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*c;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return ((char *) ft_calloc(1, sizeof(char)));
	if (len > s_len - start)
		len = s_len - start;
	c = (char *) ft_calloc((len + 1), sizeof(char));
	if (!c)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		c[i] = s[start + i];
		i++;
	}
	return (c);
}
