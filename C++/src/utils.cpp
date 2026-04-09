#include "../rush02.hpp"

// Print the correct error code before exiting the program.
int exit_error(int code)
{
	if (code == 1)
		std::cout << "Error" << std::endl;
	else if (code == -1)
		std::cout << "Dict error" << std::endl;
	return (EXIT_FAILURE);
}