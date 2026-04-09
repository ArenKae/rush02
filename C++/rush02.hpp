#ifndef RUSH02_HPP
#define RUSH02_HPP

#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <cctype>
#include <stdexcept>
#include <map>

# define ERROR 1
# define DICT_ERROR -1

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define RESET "\033[0m"

typedef std::map<std::string, std::string> DictMap;

DictMap		init_dict(std::ifstream &file);
std::string trim(std::string str);
bool 		is_digits(const std::string &s);
int			exit_error();


#endif