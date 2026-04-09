#include "../rush02.hpp"

// Trim a string of leading and trailing spaces.
std::string trim(std::string str)
{
    std::size_t start = 0;
    while (start < str.size() && std::isspace(static_cast<unsigned char>(str[start])))
        ++start;

	// Cast to <unsigned char> to avoid UB of isspace()
    std::size_t end = str.size();
    while (end > start && std::isspace(static_cast<unsigned char>(str[end - 1])))
        --end;

	// Return a string_view (no copy) of the string str without leading and trailing spaces.
    return str.substr(start, end - start);
}

// Check if the numeric key from the dictionary is a number.
bool is_digits(const std::string &num)
{
    if (num.empty())
        return false;

    for (char c : num)
    {
        if (!std::isdigit(static_cast<unsigned char>(c)))
            return false;
    }
    return true;
}

// Print the correct error code before exiting the program.
int exit_error()
{
	std::cout << RED << "Error" << RESET << std::endl;
	return (EXIT_FAILURE);
}