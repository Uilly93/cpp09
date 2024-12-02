#include "../includes/BitcoinExchange.hpp"
#include "../includes/colors.hpp"
#include <cstdlib>
#include <fstream>
#include <map>

bool check_date_error(const Date &date);

Date::Date() : year(-1), month(-1), day(-1) {
}

Date::Date(const std::string &dateStr) {
	if (dateStr.size() != 10 || dateStr[4] != '-' || dateStr[7] != '-') {
		year = -1;
		month = -1;
		day = -1;
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
			std::string err = line + ": no ',' found in database";
			throw std::invalid_argument(err);
		}
		std::string str_date = line.substr(0, line.find(','));
		std::string num = line.substr(line.find(',') + 1);
		if (num == "")
			throw std::invalid_argument("invalid Database value");
		Date date(str_date);
		if (check_date_error(date))
			throw std::invalid_argument("invalid Database date");
		char *ptr;
		float value = std::strtold(num.c_str(), &ptr);
		if (*ptr != 0)
			throw std::invalid_argument("invalid Database value");
		map[date] = value;
	}
	if (map.empty())
		throw std::invalid_argument("empty Database");
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

float getValue(std::string &line) {
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

bool is_date_superior(Date &date, std::map<Date, float>::iterator it) {
	if (date.year > it->first.year) {
		return true;
	} else if (date.year == it->first.year) {
		if (date.month > it->first.month) {
			return true;
		} else if (date.month == it->first.month) {
			if (date.day >= it->first.day) {
				return true;
			}
		}
	}
	return false;
}

void compare_with_db(Date &date, float value, std::map<Date, float> db) {
	if(db.empty()){
		std::cerr << RED << "Database is empty" << std::endl;
		return ;
	}
	std::map<Date, float>::iterator it = db.begin();
	float multiplier = it->second;
	if (!is_date_superior(date, it)) {
		std::cerr << date.year << "-" << date.month << "-" << date.day << " => "
				  << "date too old" << std::endl;
		return;
	}
	while (it != db.end() && is_date_superior(date, it)) {
		multiplier = it->second;
		++it;
	}
	if (it->first.year == date.year && it->first.month == date.month && it->first.day == date.day)
		multiplier = it->second;
	else {
		it--;
		multiplier = it->second;
	}
	std::cout << date.year << "-" << date.month << "-" << date.day << " => " << value << " = "
			  << value * multiplier << std::endl;
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
		compare_with_db(date, value, db);
	}
}