#include "../rush02.hpp"


void check_args_errors(int ac, char **av)
{
	char *input;
	if (ac < 2 || ac > 3)
		throw std::runtime_error("Error: wrong number of arguments");
	if (ac == 2)
		input = av[1];
	else
		input = av[2];
	for (int i = 0; input[i]; i++)
		if (!std::isdigit(input[i]))
			throw std::runtime_error("Error: invalid argument");
}

DictMap init_dict(std::ifstream& file)
{
	DictMap dict;
    std::string line;
    int line_number = 0;

    while (std::getline(file, line))
    {
        ++line_number;

        std::string trimmed_line = trim(line);

        // Skip empty or whitespace-only lines
        if (trimmed_line.empty())
            continue;

        std::size_t colon_pos = trimmed_line.find(':');

        // Reject lines with no ':'
        if (colon_pos == std::string::npos)
            throw std::runtime_error("Dict Error (line " + std::to_string(line_number) + "): missing ':'");

        std::string key = trim(trimmed_line.substr(0, colon_pos));
        std::string value = trim(trimmed_line.substr(colon_pos + 1));

        // Reject missing key or value
        if (key.empty())
            throw std::runtime_error("Dict Error (line " + std::to_string(line_number) + "): missing key");

        if (value.empty())
            throw std::runtime_error("Dict Error (line " + std::to_string(line_number) + "): missing value");

        // Reject non-numeric keys
        if (!is_digits(key))
            throw std::runtime_error("Dict Error (line " + std::to_string(line_number) + "): key is not numeric");

        dict[key] = value;
    }
	return dict;
}

int	main(int ac, char **av)
{
	try
	{
		check_args_errors(ac, av);

		std::string filename;
		std::string input;
		if (ac == 3)
			filename = av[1], input = av[2];
		else
			filename = "../numbers.dict", input = av[1];

		// Open the dict file
		std::ifstream file(filename);
		if (!file.is_open() || file.fail())
			return (exit_error());

		// Parse the file and initialize a map with the dict values
		DictMap dict = init_dict(file);

		// for (const auto& [key, value] : dict)
		// 	std::cout << "|" << key << "|" << value << "|" << std::endl;

		std::cout << input << std::endl;

	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
		return(EXIT_FAILURE);
	}
	return(EXIT_SUCCESS);
}