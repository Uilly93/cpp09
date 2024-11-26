#include "../includes/BitcoinExchange.hpp"
#include <cstddef>
#include <map>

int main(int ac, char**av){
	if (ac != 2)
		return 1;
	// Date date;
	// (void)date;
	std::map<Date, double> map;
	std::string path(av[1]);
	fill_map(map, path);
}