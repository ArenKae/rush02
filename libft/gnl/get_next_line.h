/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:14:52 by acosi             #+#    #+#             */
/*   Updated: 2026/03/23 16:45:06 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include "../include/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);
char	*extract_line(char *stash);
char	*clean_stash(char *stash);
char	*free_str(char *stash, char *line);
char	*ft_strchr(char *str, int c);
char	*ft_strjoin(char *stash, const char *line);
char	*ft_join(char *dest, char *s1, char *s2);
#endif