#include "../include/rush02.h"

// For numbers under 100, check if it is an "initial entry" from the original dictionary.
// Prevent arbitrary additionnal entries to take over the parsing logic if an exact match is found.
// Ex: if the dictionary adds the entry "54: fifty-four", the program must still use the initial 
// entries "50: fifty" and "4: four" to write the number.
// The initial entries are :
//   - 0 to 19
//   - exact tens: 20, 30,..., 90
//   - 100
//   - powers of 1000
bool	is_base_under_100(char *num)
{
	int	len;

	len = ft_strlen(num);
	if (len == 1)
		return (true);
	if (len == 2)
	{
		if (num[0] == '1')
			return (true);
		if (num[1] == '0' && num[0] >= '2' && num[0] <= '9')
			return (true);
	}
	return (false);
}

// Trim a string of any leading or trailing spaces.
char	*ft_trim(char *str)
{
	char	*start;
	char	*end;
	int		i;
	
	start = str;
	while (ft_isspace(*start))
		start++;
	end = start + ft_strlen(start);
	while (end > start && ft_isspace(end[-1]))
		end--;
	*end = '\0';
	i = 0;
	while (start[i])
	{
		str[i] = start[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

// Check for errors in the dictionary.
int	check_dict_errors(char **split)
{
	// Check if split is valid and has at least 2 elements
	if (!split || !split[0] || !split[1])
	{
		if (split)
		{
			free(split[0]);
			free(split[1]);
			free(split);
		}
		return (1);
	}

	// Check if split has more than 2 elements, for example if the line had multiples ':'
	int i = 0;
	while (split[i])
		++i;
	if (i > 2)
	{
		for (int j = 0; split[j]; j++)
			free(split[j]);
		free(split);
		return (1);
	}

	// Check if the key is a number
	char *cpy = ft_trim(split[0]);
	for (int j = 0; cpy[j]; ++j)
	{
		if (!ft_isdigit(split[0][j]))
		{
			free(split[0]);
			free(split[1]);
			free(split);
			return (1);
		}
	}
	
	// Check if the value is made of printable characters
	for (int j = 0; split[1][j]; ++j)
	{
		if (!ft_isprint(split[1][j]) && split[1][j] != '\n')
		{
			free(split[0]);
			free(split[1]);
			free(split);
			return (1);
		}
	}
	return (0);
}

// Split the buffer returned by gnl() around the ':' separator.
// Check for formating errors, and create a new node in the
// linked list to store the key and the value of the dictionary,
// trimmed of any leading or trailing spaces.
t_dict	*new_dict_node(char *buffer)
{
	char	**split;
	t_dict	*node;

	split = ft_split(buffer, ':');
	if (check_dict_errors(split))
		return (NULL);
	node = malloc(sizeof(t_dict));
	if (!node)
	{
		free(split[0]);
		free(split[1]);
		free(split);
		return (NULL);
	}
	node->key = ft_trim(split[0]);
	node->value = ft_trim(split[1]);
	node->next = NULL;
	free(split);
	return (node);
}

// Free the linked list before exiting the program.
void ft_free(t_dict *dict)
{
	t_dict *temp;

	while (dict != NULL)
	{
		temp = dict;
		dict = dict->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

// Print the correct error code before exiting the program.
int exit_error(int code)
{
	if (code == 1)
		ft_printf("Error\n");
	else if (code == -1)
		ft_printf("Dict error\n");
	return (EXIT_FAILURE);
}
