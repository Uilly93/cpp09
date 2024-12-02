#ifndef BITCOIN_HPP
#define BITCOIN_HPP

#include <iostream>
#include <map>

class Date {
	public:
	int year;
	int month;
	int day;
	Date();
	Date(const std::string &dateStr);
	Date(const Date &src);
	~Date();
	Date &operator=(const Date &src);
	bool operator<(const Date &other) const;
};

std::ostream &operator<<(std::ostream &os, const Date &date);

std::map<Date, float> fill_data_base(std::string &path);
void parse_input(std::string &input, std::map<Date, float> db);

#endif