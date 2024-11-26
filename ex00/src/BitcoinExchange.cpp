#include "../includes/BitcoinExchange.hpp"
#include "../includes/colors.hpp"
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>

Date convert_date(std::string str) {
	if (str.empty())
		throw std::invalid_argument("invalide date format");
	int first_dash = str.find('-');
	int second_dash = str.find_last_of('-');
	std::string y_str = str.substr(0, first_dash);
	std::string m_str = str.substr(first_dash + 1, second_dash - first_dash - 1);
	std::string d_str = str.substr(second_dash + 1);
	// std::cout << y_str << " " << m_str << " " << d_str << RESET << std::endl;
	Date date;
	date.year = std::atoi(y_str.c_str());
	date.month = std::atoi(m_str.c_str());
	date.day = std::atoi(d_str.c_str());
	return date;
}

// bool check_line(std::string line){

// }

void fill_map(std::map<Date, double> &map, std::string &path) {
	// (void)date;
	(void)map;
	// int i = 0;
	std::ifstream file(path);
	if (!file.is_open())
		throw std::invalid_argument("invalid file");

	for (std::string line; std::getline(file, line);) {
		while (line == "date,exchange_rate" || line.empty()) {
			std::getline(file, line);
		}
		std::size_t pos = line.find(',');
		if (pos == std::string::npos)
			throw std::invalid_argument("invalid line format");
		std::string str_date = line.substr(0, line.find(','));
		std::string num = line.substr(line.find(',') + 1);
		Date date = convert_date(str_date);
		double value = std::atof(num.c_str());
		std::cout << date.year << " " << date.month << " " << date.day << " " << value << RESET << std::endl;

		map[date] = value;
		// std::map<Date, double>::iterator it = map.begin();
		// it->first.
		// std::cout << map[] << "message" << RESET << std::endl;
		// Date date;
		// date.year =
		// date.month =
		// date.day =
		// if (num == "")
		// std::cout << date << "   " << value << std::endl;
	}
	file.close();
}