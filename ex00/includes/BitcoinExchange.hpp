#ifndef BITCOIN_HPP
#define BITCOIN_HPP

#include "colors.hpp"
#include <iostream>
#include <map>
#include <ostream>
#include <vector>

class Date {
	public:
	int year;
	int month;
	int day;
	Date();
	Date(const std::string &dateStr);
	~Date();
	bool operator<(const Date &other) const;
};

std::ostream &operator<<(std::ostream &os, const Date &date);

std::map<Date, float> fill_data_base(std::string &path);

#endif