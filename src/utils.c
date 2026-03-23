#include "../include/rush.h"

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

t_dict	*new_dict_node(char *buffer)
{
	char	**split;
	t_dict	*node;

	split = ft_split(buffer, ':');
	if (!split || !split[0] || !split[1])
	{
		if (split)
		{
			free(split[0]);
			free(split[1]);
			free(split);
		}
		return (NULL);
	}
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
