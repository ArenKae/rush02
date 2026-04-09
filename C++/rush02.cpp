#include "./rush02.hpp"

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
		if (!std::isdigit(input[i]))
			return (1);
	return (0);
}

int	main(int ac, char **av)
{
	if (check_errors(ac, av))
		return (exit_error(ERROR));


	return 0;
}