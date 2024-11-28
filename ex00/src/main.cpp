#include "../includes/BitcoinExchange.hpp"
#include <cstddef>
#include <exception>
#include <iomanip>
#include <ios>
#include <map>

int main(int ac, char **av) {
	// if (ac != 2)
	// 	return 1;
	(void)ac;
	(void)av;
	std::string path("data.csv");
	std::string input = av[1];
	try {
		std::map<Date, float> data_base = fill_data_base(path);
		parse_input(input, data_base);
		// for (std::map<Date, float>::iterator it = data_base.begin(); it != data_base.end(); it++)
		// 	std::cout << it->first << " " << it->second << RESET << std::endl;

	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	// std::cout << it->first.year << " " << it->first.month << " " << it->first.day << " "
	// 		  << it->second << RESET << std::endl;
}