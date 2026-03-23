/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:12:50 by acosi             #+#    #+#             */
/*   Updated: 2025/03/21 18:32:06 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* The main loop uses read() to write from the open fd in buffer 'line'.
In case of read errors, the free_str function is used to free all buffers.
The content of line is then transferred in the static stash with ft_strjoin().
The loop stops the first time a '\n' is found in the stash, meaning the end
of line has been reached. The extract_line function then probes the static
stash for a complete newline and sends it to the return buffer. Finally, 
 the stash is cleaned of the line that is being returned for the next
 get_next_line call. */

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	int			read_size;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!line)
		return (NULL);
	read_size = 1;
	while (!(ft_strchr(stash, '\n')) && read_size != 0)
	{
		read_size = read(fd, line, BUFFER_SIZE);
		if (read_size == -1)
		{
			stash = free_str(stash, line);
			return (NULL);
		}
		line[read_size] = '\0';
		stash = ft_strjoin(stash, line);
	}
	free(line);
	line = extract_line(stash);
	stash = clean_stash(stash);
	return (line);
}

/* Search for the current line in the static stash, then extract it to
the 'line' buffer, which serves as a return value for the main function. */

char	*extract_line(char *stash)
{
	int		i;
	char	*line;

	if (!stash || !stash[0])
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	i += (stash[i] == '\n');
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

/* A clean new stash is created without the caracters of the line that was just
read. This new stash is then assigned to the static stash for the next 
get_next_line call. The old stash is freed to avoid leaks. */

char	*clean_stash(char *stash)
{
	char	*new_stash;
	int		i;
	int		j;

	i = 0;
	if (stash[i] == '\0')
	{
		free(stash);
		return (NULL);
	}
	while (stash[i] && stash[i] != '\n')
		i++;
	i += (stash[i] == '\n');
	new_stash = malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
	if (!new_stash)
		return (NULL);
	j = 0;
	while (stash[i + j])
	{
		new_stash[j] = stash[i + j];
		j++;
	}
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}
