#include "../includes/colors.hpp"
#include <cstddef>
#include <exception>
#include <fstream>
#include <map>
#include <sstream>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include "../includes/BitcoinExchange.hpp"

void fill_map(Date &date, std::map<Date, double> &map, std::string path){
	int i = 0;
	std::ifstream file(path);
	if(!file.is_open())
		throw std::invalid_argument("invalid file");

	for(std::string line; std::getline(file, line);){
		std::size_t pos = line.find(',');
		if(pos == std::string::npos)
			throw std::invalid_argument("invalid line format");
		std::string date = line.substr(0, line.find(','));
		double value = std::stod(line.substr(line.find(',') + 1));
	}
}