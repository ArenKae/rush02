# include "../include/rush.h"

// Check if the input number matches a key in the dictionary and print its value if it does. 
// If newline is 1, print a \n after the value. If it's 0, print a space. If its -1, print nothing. 
// If c is -1 instead of 0, it means we are just checking if input is a match, and don't need to print anything.
bool exact_match(char *input, t_dict *dict, int newline, char c)
{
	while (dict != NULL)
	{
		if (!ft_strncmp(input, dict->key, ft_strlen(input) + 1))
		{
			if (newline == 1 && (c != -1))
				ft_printf("%s\n", dict->value);
			else if (newline == 0 && (c != -1))
				ft_printf("%s ", dict->value);
			else if (newline == -1 && (c != -1))
				ft_printf("%s", dict->value);
			return (true);
		}
		dict = dict->next;
	}
	return (false);
}

// Print the input number as a combination of tens and units (for example, 42 = 40 + 2).
// The tens and units arrays are indexed by the digit of the input 
// (for example, tens[4] = "40" and units[2] = "2"), to get the correct value from the dictionary.
void under_100(char *input, t_dict *dict)
{
	char *tens[] = {"20", "30", "40", "50", "60", "70", "80", "90"};
	char *units[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
	if (input[0] != '0')
	{
		if (!exact_match(tens[input[0] - '2'], dict, 0, 0))
			ft_printf("Dict Error\n");
	}
	if (input[1] != '0')
	{
		if (!exact_match(units[input[1] - '0'], dict, 0, 0))
			ft_printf("Dict Error\n");
	}
}

// Count the number of spaces needed to split the input number into groups of 
// 3 digits (for example, 1234567 = 1 234 567).
int count_spaces(int size)
{
	if (size % 3 == 0)
		return ((size / 3) - 1);
	else
		return ((size / 3));
}

// Split the input number into groups of 3 digits, starting from the right.
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

// Trim leading zeros from the input number to avoid printing scales 
// for empty groups (for example, 000 = 0, 0001 = 1).
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

//Write the current group of 3 digits with the correct scale (thousand, million, billion, etc.).
void write_number(t_dict *dict, char **tab, int i, char *scales[], int spaces)
{
	// If the current group of digits is only zeros, don't print anything
	if (!ft_strncmp(tab[i], "000", 3))
		return ;
	char *num = tab[i];
	num = trim_zeros(num, 3);
	int len = ft_strlen(num);
	if (len == 1 || len == 2)
	{
		if (exact_match(num, dict, 0, 0))
			;
		else
			under_100(num, dict);
	}
	else if (len == 3)
	{
		if (num[0] != '0')
		{
			// Isolate the first digit of the current group and perform a dictionary lookup
			// for the hundreds place (ex: 100 = one + hundred)
			char digit[2];
			digit[0] = num[0];
			digit[1] = '\0';
			exact_match(digit, dict, 0, 0);
			ft_printf("%s ", scales[0]); // scales[0] = "hundred"
		}
		char cpy[3];
		cpy[0] = num[1];
		cpy[1] = num[2];
		cpy[2] = '\0';
		under_100(cpy, dict);
	}
	// If the current group of digits is not the last one, print the scale.
	if (tab[i + 1])
		ft_printf("%s ", scales[spaces]);
}

// Parse the input number and print it in words using the dictionary and the scales.
void parse_input(char *input, t_dict *dict, char *scales[])
{
	int size = ft_strlen(input);
	char **split_tab;

	// If the number is less than 100, we can directly print it using the dictionary.
	if (size < 3)
	{
		ft_printf("%s\n", input);
		// If no exact match is found, we try to print it as a number under 100 (for example, 42 = 40 + 2).
		if (!exact_match(input, dict, 1, 0))
		{
			under_100(input, dict);
			ft_printf("\n");
		}
		return ;
	}
	else
	{
		// For numbers greater than or equal to 100, we split the input into groups of 3 digits, 
		// and print each group with the correct scale (thousand, million, billion, etc.).
		input = trim_zeros(input, size); // Trim leading zeros to avoid printing scales for empty groups
		size = ft_strlen(input); // Update size after trimming zeros
		split_tab = split_input(input); // Split the input into groups of 3 digits
		for (int i = 0; split_tab[i]; i++)
			ft_printf("%s ", split_tab[i]);
		ft_printf("\n");
		int spaces = count_spaces(size); // The number of spaces gives us the index of the scale array for each group of 3 digits
		for (int i = 0; split_tab[i]; i++)
			write_number(dict, split_tab, i, scales, spaces--); // scales is decremented every time to get the correct scale (thousand, million, billion, etc.)
		ft_printf("\n");

		// Leaks
		for (int i = 0; split_tab[i]; i++)
			free(split_tab[i]);
		free(split_tab);
		return ;
	}
}

// Check if the key is a scale (thousand, million, billion, etc.) and return its index in the scales array, or -1 if it's not a scale.
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
	// A scale must have a number of zeros that is a multiple of 3, and at least 3 (thousand).
	if (count_zeros % 3 != 0 || count_zeros < 3)
		return (-1);

	// The index of the scale in the array is the number of groups of 3 zeros it has (thousand = 1, million = 2, billion = 3, etc.).
	return (count_zeros / 3);
}

// Parse the dictionary and store the values of the scales (thousand, million, billion, etc.) in an array for easy access later.
void parse_dict(t_dict *dict, char *scales[])
{
	int i = 0;

	while (dict != NULL)
	{
		if (exact_match("100", dict, -1, -1))
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
		return (1);
	if (ac == 2)
		input = av[1];
	else
		input = av[2];
	for (int i = 0; input[i]; i++)
		if (!ft_isdigit(input[i]))
			return (1);
	return (0);
}

int	main(int ac, char **av)
{
	if (check_errors(ac, av))
		return (exit_error(ERROR));

	int fd;
	char *file;
	char *input;
	if (ac == 3)
		file = av[1], input = av[2];
	else
		file = "../numbers.dict", input = av[1];
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (exit_error(ERROR));

	// Read the dictionary and store each line in a linked list
	char	*buffer;
	t_dict	*dict = NULL;
	t_dict	*new_node;
	while ((buffer = get_next_line(fd)))
	{
		// Skip empty lines
		if (buffer[0] == '\n')
		{
			free(buffer);
			continue ;
		}
		// Each line = 1 node
		new_node = new_dict_node(buffer);
		free(buffer);
		if (!new_node)
		{
			ft_free(dict);
			close(fd);
			return (exit_error(DICT_ERROR));
		}
		new_node->next = dict;
		dict = new_node;
	}

	// Create an array to store the scales (thousand, million, billion, etc.)
	char	**scales;
	scales = malloc(sizeof(char *) * 32);
	if (scales == NULL)
		return (exit_error(ERROR));
	scales[0] = "";

	parse_dict(dict, scales);
	parse_input(input, dict, scales);

	ft_free(dict);
	free(scales);
	close(fd);
	return (EXIT_SUCCESS);
}
