# include "../include/rush.h"

bool exact_match(char *input, t_dict *dict, bool newline, char c)
{
	if (!input)
	{
		char str[2];
		str[0] = c;
		str[1] = '\0';
		input = str;
	}

	while (dict != NULL)
	{
		if (!ft_strncmp(input, dict->key, ft_strlen(input) + 1))
		{
			if (newline && (c != -1))
				printf("%s\n", dict->value);
			else if (c != -1)
				printf("%s ", dict->value);
			return (true);
		}
		dict = dict->next;
	}
	return (false);
}

void under_100(char *input, t_dict *dict)
{
	char *tens[] = {"20", "30", "40", "50", "60", "70", "80", "90"};
	char *units[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

	if (input[0] != '0')
	{
		if (!exact_match(tens[input[0] - '2'], dict, false, 0))
			printf("Dict Error\n");
	}
	if (input[1] != '0')
	{
		if (!exact_match(units[input[1] - '0'], dict, false, 0))
			printf("Dict Error\n");
	}
}

int count_spaces(int size)
{
	if (size % 3 == 0)
		return ((size / 3) - 1);
	else
		return ((size / 3));
}

char **split_input(char *input)
{
	int i, j, count;
	int size = ft_strlen(input);
	char **tab;
	count = count_spaces(size);

	char *tmp = malloc(sizeof(char) * (size + count + 1));
	tmp[size + count] = '\0';

	i = 0;
	while (input[i])
		i++;

	j = size + count - 1;
	count = 0;
	while (i-- > 0)
	{
		tmp[j] = input[i];
		count++;
		if (count == 3 && j > 0)
		{
			j--;
			tmp[j] = ' ';
			count = 0;
		}
		j--;
	}
	tab = ft_split(tmp, ' ');
	free(tmp);
	return tab;
}

char *trim_zeros(char *input, int size)
{
	if (input[0] != '0' || size == 1)
		return input;
	
	int i = 0, j = 0;
	while (input[i] == '0')
		i++;
	if (i == size)
		return ("0");
	for (j = 0; input[i]; i++)
		input[j++] = input[i];
	input[j] = '\0';
	return input;
}

void write_number(t_dict *dict, char **tab, int i, char *scales[], int spaces)
{
	// Si le nombre est 000, on ne l'affiche pas
	if (!ft_strncmp(tab[i], "000", 3))
		return ;
	char *input = tab[i];
	input = trim_zeros(input, 3);
	int len = ft_strlen(input);
	if (len == 1 || len == 2)
	{
		if (exact_match(input, dict, false, 0))
			;
		else
		{
			under_100(input, dict);
		}
	}
	else if (len == 3)
	{
		if (input[0] != '0')
		{
			exact_match(NULL, dict, false, tab[i][0]);
			printf("%s ", scales[0]);
		}
		char cpy[3];
		cpy[0] = input[1];
		cpy[1] = input[2];
		cpy[2] = '\0';
		under_100(cpy, dict);
	}
	if (tab[i + 1])
		printf("%s ", scales[spaces]);
}

void parse_input(char *input, t_dict *dict, char *scales[])
{
	int size = ft_strlen(input);
	char **split_tab;

	if (size < 3)
	{
		if (!exact_match(input, dict, true, 0))
			under_100(input, dict);
		printf("\n");
		return ;
	}
	else
	{
		input = trim_zeros(input, size);
		split_tab = split_input(input);
		for (int i = 0; split_tab[i]; i++)
			printf("%s ", split_tab[i]);
		printf("\n");
		int spaces = count_spaces(size);
		for (int i = 0; split_tab[i]; i++)
			write_number(dict, split_tab, i, scales, spaces--);
		printf("\n");

		// Leaks
		for (int i = 0; split_tab[i]; i++)
			free(split_tab[i]);
		free(split_tab);
		return ;
	}
}

int get_scale_index(const char *key)
{
	int i = 1;
	int count_zeros = 0;

	if (key[0] != '1')
		return (-1);

	while (key[i])
	{
		if (key[i] != '0')
			return (-1);
		count_zeros++;
		i++;
	}
	if (count_zeros % 3 != 0 || count_zeros < 3)
		return (-1);

	return (count_zeros / 3);
}


void parse_dict(t_dict *dict, char *scales[])
{
	int i = 0;

	while (dict != NULL)
	{
		if (exact_match("100", dict, true, -1))
				scales[0] = dict->value;

		if ((i = get_scale_index(dict->key)) >= 1)
			scales[i] = dict->value;
		dict = dict->next;
	}
}

int check_errors(int ac, char **av)
{
	char *input;
	if (ac < 2 || ac > 3)
	{
		printf("Error\n");
		return (1);
	}
	if (ac == 2)
		input = av[1];
	else
		input = av[2];
	for (int i = 0; input[i]; i++)
		if (!ft_isdigit(input[i]))
		{
			printf("Error\n");
			return (1);
		}
	return (0);
}

int	main(int ac, char **av)
{
	int		fd;
	char	*buffer;
	char	**scales;
	t_dict	*dict = NULL;
	t_dict	*new_node;

	if (check_errors(ac, av))
		return (EXIT_FAILURE);

	scales = malloc(sizeof(char *) * 32);
	if (scales == NULL)
		return (EXIT_FAILURE);
	scales[0] = "";

	fd = open("numbers.dict", O_RDONLY);
	if (fd == -1)
		return (EXIT_FAILURE);

	while ((buffer = get_next_line(fd)))
	{
		if (buffer[0] == '\n')
		{
			free(buffer);
			continue ;
		}

		new_node = new_dict_node(buffer);
		free(buffer);
		if (!new_node)
		{
			ft_free(dict);
			close(fd);
			return (1);
		}
		new_node->next = dict;
		dict = new_node;
	}

	parse_dict(dict, scales);
	parse_input(av[1], dict, scales);

	ft_free(dict);
	free(scales);
	close(fd);
	return (EXIT_SUCCESS);
}
