#ifndef BITCOIN_HPP
#define BITCOIN_HPP

#include "colors.hpp"
#include <iostream>
#include <map>
#include <vector>

struct Date {
	int year;
	int month;
	int day;
};

void fill_map(std::map<Date, double> &map, std::string path);

// struct Format {
// 	std::map<Date, double> map;
// };

// class Bitcoin {
// 	public:
// 	// Constructor
// 	Bitcoin();
// 	// Bitcoin(parametric constructor);
// 	// Bitcoin(const Bitcoin &src);

// 	// Destructor
// 	~Bitcoin();

// 	// Operator Overload
// 	// Bitcoin &operator=(const Bitcoin &src);

// 	// Methods
// 	private:
// 	std::map<Date, double> map;
// };

#endif