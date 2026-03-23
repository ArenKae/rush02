/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:13:20 by acosi             #+#    #+#             */
/*   Updated: 2026/03/23 16:46:02 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Libft function that locates the first occurence of 'c' in the string str,
and returns a pointer to it. The '\0' is considered part of the string and is
specifically managed. This is used in the main function to find occurences of
newlines characters or '\n'. */

char	*ft_strchr(char *str, int c)
{
	size_t	i;

	if (!str)
		return (NULL);
	if (c == 0)
	{
		i = ft_strlen(str);
		return (&str[i]);
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return (&str[i]);
		i++;
	}
	return (NULL);
}

/* Libft function that allocates and returns  a new string, which is the result
of the concatenation of ’stash’ and ’line’. I also use this function to check
if the static stash is created on the first get_next_line call, and allocate
memory to it if not. */

char	*ft_strjoin(char *stash, const char *line)
{
	char	*dst;
	size_t	i;
	size_t	j;

	if (!stash)
	{
		stash = malloc(sizeof(char));
		stash[0] = '\0';
	}
	if (!stash || !line)
		return (NULL);
	dst = malloc(sizeof(char) * (ft_strlen(stash) + ft_strlen(line) + 1));
	if (!dst)
		return (NULL);
	i = -1;
	while (stash && stash[++i])
		dst[i] = stash[i];
	j = -1;
	while (line && line[++j])
		dst[i + j] = line[j];
	dst[i + j] = '\0';
	free(stash);
	return (dst);
}

/* Leak management function to free all buffers in a single call. */

char	*free_str(char *stash, char *line)
{
	free(line);
	free(stash);
	stash = NULL;
	return (stash);
}
