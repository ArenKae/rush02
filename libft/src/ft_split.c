/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:17:10 by acosi             #+#    #+#             */
/*   Updated: 2025/03/18 22:58:31 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	DESCRIPTION :
	The function ft_split allocates and returns an array of strings by 
	splitting the given string 'str' using the given separator c.

	RETURN VALUE :
	An null-terminated array of strings resulting from the split.
	NULL if the memory allocation fails.
*/

#include "../include/libft.h"

/*	word_count :
*		Parses the string and increment a counter every time an instance of 
*		separators is encountered, returning the total number of words in which 
*		'str' should be splitted.
*/

int	wordcount(char const *str, char c)
{
	int	i;
	int	word_count;

	i = 0;
	word_count = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			word_count++;
			while (str[i] != '\0' && str[i] != c)
				i++;
		}
		else
			i++;
	}
	return (word_count);
}

/*	strlen_word :
		Parses the string 'str' while incrementing a counter until a separator
		is encountered, returning the length of the current word to write.
*/

int	strlen_word(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

/*	write_word :
		Calculates the size of the current word and allocates memory for it.
		Writes the word without separators and null-terminate it.
*/

char	*write_word(char const *str, char c)
{
	int		len_word;
	int		i;
	char	*word;

	i = 0;
	len_word = strlen_word(str, c);
	word = malloc(sizeof(char) * (len_word + 1));
	while (i < len_word)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *str, char c)
{
	char	**dst;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	dst = malloc(sizeof(char *) * (wordcount(str, c) + 1));
	if (!dst)
		return (NULL);
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str != '\0')
		{
			dst[i] = write_word(str, c);
			i++;
		}
		while (*str && *str != c)
			str++;
	}
	dst[i] = NULL;
	return (dst);
}
