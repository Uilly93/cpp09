#include "../includes/BitcoinExchange.hpp"
#include "../includes/colors.hpp"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <istream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>

bool check_date_error(const Date &date);

Date::Date() : year(0), month(0), day(0) {
}

Date::Date(const std::string &dateStr) {
	if (dateStr.size() != 10 || dateStr[4] != '-' || dateStr[7] != '-') {
		year = -1;
		month = -1;
		day = -1;
		// std::string err = dateStr + ": invalid date format";
		// throw std::invalid_argument(err);
	} else {
		int first_dash = dateStr.find('-');
		int second_dash = dateStr.rfind('-');
		std::string y_str = dateStr.substr(0, first_dash);
		std::string m_str = dateStr.substr(first_dash + 1, second_dash - first_dash - 1);
		std::string d_str = dateStr.substr(second_dash + 1);
		year = std::atoi(y_str.c_str());
		month = std::atoi(m_str.c_str());
		day = std::atoi(d_str.c_str());
	}
}

Date::Date(const Date &src) {
	*this = src;
}

Date::~Date(){};

bool Date::operator<(const Date &other) const {
	if (year != other.year)
		return year < other.year;
	if (month != other.month)
		return month < other.month;
	return day < other.day;
}

Date &Date::operator=(const Date &src) {
	if (this != &src) {
		this->year = src.year;
		this->month = src.month;
		this->day = src.day;
	}
	return *this;
}

std::ostream &operator<<(std::ostream &os, const Date &date) {
	os << date.year << "/" << date.month << "/" << date.day;
	return os;
}

std::map<Date, float> fill_data_base(std::string &path) {
	std::ifstream file(path.c_str());
	if (!file.is_open())
		throw std::invalid_argument("failed to open DateBase file");
	std::map<Date, float> map;
	for (std::string line; std::getline(file, line);) {
		while (line == "date,exchange_rate" || line.empty()) {
			std::getline(file, line);
		}
		std::size_t pos = line.find(',');
		if (pos == std::string::npos) {
			std::string err = line + ": no ',' found";
			throw std::invalid_argument(err);
		}
		std::string str_date = line.substr(0, line.find(','));
		std::string num = line.substr(line.find(',') + 1);
		if (num == "")
			throw std::invalid_argument("invalid DB value");
		Date date(str_date);
		if (check_date_error(date))
			throw std::invalid_argument("invalid DB date");
		char *ptr;
		float value = std::strtold(num.c_str(), &ptr);
		if (*ptr != 0)
			throw std::invalid_argument("invalid DB value");
		// std::cout << num << std::endl;
		map[date] = value;
	}
	return map;
}

Date getDate(std::string &line) {
	std::size_t pos = line.find(" | ");
	if (pos == std::string::npos) {
		std::string err = line + ": invalid line format";
		throw std::invalid_argument(err);
	}
	std::string str_date = line.substr(0, pos);
	Date date(str_date);
	return date;
}

int getValue(std::string &line) {
	std::string num = line.substr(line.find('|') + 1);
	float value = std::strtold(num.c_str(), NULL);
	return value;
}

bool check_date_error(const Date &date) {
	if (date.year < 1 || date.year > 9999)
		return true;
	if (date.month < 1 || date.month > 12)
		return true;
	if (date.day < 1 || date.day > 31)
		return true;
	if (date.month == 2) {
		bool is_leap_year = (date.year % 4 == 0 && date.year % 100 != 0) || (date.year % 400 == 0);
		if (is_leap_year) {
			if (date.day > 29)
				return true;
		} else {
			if (date.day > 28)
				return true;
		}
	} else if (date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11) {
		if (date.day > 30)
			return true;
	}
	return false;
}

int check_inputs(std::string line) {
	std::size_t pos = line.find(" | ");
	if (pos == std::string::npos) {
		std::cerr << line << " : invalid input line" << std::endl;
		return 1;
	}
	std::string str_date = line.substr(0, line.find(" "));
	std::string num = line.substr(line.find("| ") + 1);
	Date date(str_date);
	if (check_date_error(date)) {
		std::cerr << line << " : invalid input date" << std::endl;
		return 1;
	}
	if (num == "") {
		std::cerr << line << " : invalid input number" << std::endl;
		return 1;
	}
	char *ptr;
	float value = std::strtold(num.c_str(), &ptr);
	if (*ptr != 0 || value > 1000 || value < 0) {
		std::cerr << line << " : invalid input number" << std::endl;
		return 1;
	}
	return 0;
}

void parse_input(std::string &input, std::map<Date, float> db) {
	(void)db;
	std::ifstream file(input.c_str());
	if (!file.is_open())
		throw std::invalid_argument("failed to open Input file");
	for (std::string line; std::getline(file, line);) {
		while (line == "date | value" || line.empty()) {
			std::getline(file, line);
		}
		if (check_inputs(line))
			continue;
		Date date = getDate(line);
		float value = getValue(line);
		std::cout << date.year << "-" << date.month << "-" << date.day << " | " << value << RESET
				  << std::endl;
	}
}