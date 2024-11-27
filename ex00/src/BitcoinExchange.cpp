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
#include <map>

// bool check_format(std::string &str) {

// }
Date::Date() : year(0), month(0), day(0) {
}

Date::Date(const std::string &dateStr) {
	if (dateStr.size() != 10 || dateStr[4] != '-' || dateStr[7] != '-') {
		std::string err = dateStr + ": invalid date format";
		throw std::invalid_argument(err);
	}
	int first_dash = dateStr.find('-');
	int second_dash = dateStr.rfind('-');
	std::string y_str = dateStr.substr(0, first_dash);
	std::string m_str = dateStr.substr(first_dash + 1, second_dash - first_dash - 1);
	std::string d_str = dateStr.substr(second_dash + 1);
	year = std::atoi(y_str.c_str());
	month = std::atoi(m_str.c_str());
	day = std::atoi(d_str.c_str());
}

Date::~Date(){};

bool Date::operator<(const Date &other) const {
	if (year != other.year)
		return year < other.year;
	if (month != other.month)
		return month < other.month;
	return day < other.day;
}

std::ostream &operator<<(std::ostream &os, const Date &date) {
	os << date.year << " " << date.month << " " << date.day;
	return os;
}

std::map<Date, float> fill_data_base(std::string &path) {
	std::ifstream file(path.c_str());
	if (!file.is_open())
		throw std::invalid_argument("invalid file");
	std::map<Date, float> map;
	for (std::string line; std::getline(file, line);) {
		while (line == "date,exchange_rate" || line.empty()) {
			std::getline(file, line);
		}
		std::size_t pos = line.find(',');
		if (pos == std::string::npos) {
			std::string err = line + ": invalid line format";
			throw std::invalid_argument(err);
		}
		std::string str_date = line.substr(0, line.find(','));
		std::string num = line.substr(line.find(',') + 1);
		Date date(str_date);
		float value = std::strtold(num.c_str(), NULL);
		map[date] = value;
	}
	file.close();
	return map;
}