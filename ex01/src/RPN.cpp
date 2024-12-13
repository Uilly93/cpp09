#include <cctype>
#include <cstdlib>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>

int count_signs(std::string arg) {
	int count = 0;
	for (int i = 0; arg[i]; i++) {
		if (arg[i] == '/' || arg[i] == '*' || (arg[i] == '+' && !std::isdigit(arg[i + 1])) ||
			(arg[i] == '-' && !std::isdigit(arg[i + 1])))
			count++;
	}
	return count;
}

std::stack<int> fill_stack(std::string arg) {
	std::stack<int> stack;
	size_t i = 0;
	unsigned int signs = count_signs(arg);
	for (; arg[i];) {
		if (arg[i] == '*' || arg[i] == '/' || (arg[i] == '+' && !std::isdigit(arg[i + 1])) ||
			(arg[i] == '-' && !std::isdigit(arg[i + 1])) || std::isspace(arg[i])) {
			if ((arg[i] == '*' || arg[i] == '/' || arg[i] == '+' || arg[i] == '-') &&
				stack.size() < 2) {
				throw std::invalid_argument("invalid sign1");
			}
			i++;
			continue;
		}
		char *end;
		int value = std::strtold(arg.c_str() + i, &end);
		// std::cout << value << std::endl;
		stack.push(value);
		i += end - (arg.c_str() + i);
	}
	// std::cout << "i = " << stack.size() << std::endl;
	// std::cout << "sign = " << signs << std::endl;
	if (signs != stack.size() - 1)
		throw std::invalid_argument("invalid sign2");
	return stack;
}

size_t find_first_digit_from_end(const std::string &str) {
	for (size_t i = str.length(); i > 0; --i) {
		if (std::isdigit(str[i - 1])) {
			return i - 1;
		}
	}
	return std::string::npos;
}

double calcules_loop(std::string arg, std::stack<int> stack) {
	int i = 0;
	double res = stack.top();
	size_t pos = find_first_digit_from_end(arg);
	if (pos == std::string::npos)
		throw std::invalid_argument("no signs founded");
	std::string signs = arg.substr(pos);
	while (signs[i]) {
		while (signs[i] && signs[i] != '+' && signs[i] != '-' && signs[i] != '/' && signs[i] != '*')
			i++;
		stack.pop();
		double tmp = stack.top();
		if (signs[i] == '+')
			res = tmp + res;
		if (signs[i] == '-')
			res = tmp - res;
		if (signs[i] == '*')
			res = tmp * res;
		if (signs[i] == '/')
			res = tmp / res;
		i++;
	}
	return res;
}