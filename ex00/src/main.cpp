#include "../includes/BitcoinExchange.hpp"
#include "../includes/colors.hpp"

int main(int ac, char **av) {
	if (ac != 2){
		std::cerr << RED << "you need one input arg" << RESET << std::endl;
		return 1;
	}
	(void)ac;
	(void)av;
	std::string path("data.csv");
	std::string input = av[1];
	try {
		std::map<Date, float> data_base = fill_data_base(path);
		parse_input(input, data_base);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}