#include "../includes/RPN.hpp"
#include <cctype>
#include <exception>
#include <iostream>
#include <iomanip>
#include <stack>

int check_input(std::string &av) {
	for (int i = 0; av[i]; i++) {
		if (!std::isdigit(av[i]) && av[i] != '+' && av[i] != '-' && av[i] != '*' && av[i] != '/' &&
			!std::isspace(av[i]))
			return 1;
	}
	return 0;
}

int main(int ac, char **av) {
	try {
		if (ac != 2) {
			std::cerr << "Error: the program needs 1 argument" << std::endl;
			return 1;
		}

		std::string arg = av[1];
		if (check_input(arg) || arg.empty()) {
			std::cerr << "Error: incorrect input" << std::endl;
			return 1;
		}
		RPN(arg);
		std::cout << std::fixed << std::setprecision(2) << "result is: " << RPN(arg) << std::endl;
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}