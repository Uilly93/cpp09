#include <cctype>
#include <climits>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stack>
#include <stdexcept>
#include <string>

int count_signs(std::string &arg) {
	int count = 0;
	for (int i = 0; arg[i]; i++) {
		if (arg[i] == '/' || arg[i] == '*' || (arg[i] == '+' && !std::isdigit(arg[i + 1])) ||
			(arg[i] == '-' && !std::isdigit(arg[i + 1])))
			count++;
	}
	return count;
}

void check_terminated(std::string &arg) {
	for (size_t i = arg.size(); i > 0; i--) {
		if (arg[i] == '*' || arg[i] == '/' || arg[i] == '+' || arg[i] == '-')
			return;
		if (std::isdigit(arg[i]))
			throw std::invalid_argument("Error: argument terminated by digit");
	}
}

void check_format(std::string &arg) {
	std::stack<long> stack;
	size_t i = 0;
	unsigned int signs = count_signs(arg);
	for (; arg[i];) {
		if (arg[i] == '*' || arg[i] == '/' || (arg[i] == '+' && !std::isdigit(arg[i + 1])) ||
			(arg[i] == '-' && !std::isdigit(arg[i + 1])) || std::isspace(arg[i])) {
			if ((arg[i] == '*' || arg[i] == '/' || arg[i] == '+' || arg[i] == '-') &&
				stack.size() < 2) {
				throw std::invalid_argument("invalid format");
			} else if ((arg[i] == '*' || arg[i] == '/' || arg[i] == '+' || arg[i] == '-') &&
					   stack.size() < 1) {
			}
			i++;
			continue;
		}
		char *end;
		long value = std::strtold(arg.c_str() + i, &end);
		stack.push(value);
		i += end - (arg.c_str() + i);
	}
	if (signs != stack.size() - 1 || (signs == 0 && !stack.empty()))
		throw std::invalid_argument("invalid sign amount");
	check_terminated(arg);
}

int RPN(std::string &arg) {
	std::stack<long> stack;
	long res;
	check_format(arg);

	for (int i = 0; arg[i];) {
		if ((arg[i] == '+' && !std::isdigit(arg[i + 1])) ||
			(arg[i] == '-' && !std::isdigit(arg[i + 1])) || arg[i] == '*' || arg[i] == '/' ||
			std::isspace(arg[i])) {
			if (stack.size() > 1 &&
				(arg[i] == '+' || arg[i] == '-' || arg[i] == '/' || arg[i] == '*')) {
				int last_top = stack.top();
				if (last_top < std::numeric_limits<int>::min() ||
					last_top > std::numeric_limits<int>::max())
					throw std::invalid_argument("number overflow");
				stack.pop();
				if (arg[i] == '+') {
					if (stack.top() + last_top < std::numeric_limits<int>::min() ||
						stack.top() + last_top > std::numeric_limits<int>::max())
						throw std::invalid_argument("number overflow");
					res = stack.top() + last_top;
				}
				if (arg[i] == '-') {
					if (stack.top() - last_top < std::numeric_limits<int>::min() ||
						stack.top() - last_top > std::numeric_limits<int>::max())
						throw std::invalid_argument("number overflow");
					res = stack.top() - last_top;
				}
				if (arg[i] == '*') {
					if (stack.top() * last_top < std::numeric_limits<int>::min() ||
						stack.top() * last_top > std::numeric_limits<int>::max())
						throw std::invalid_argument("number overflow");
					res = stack.top() * last_top;
				}
				if (arg[i] == '/') {
					if (last_top == 0)
						throw std::invalid_argument("division by 0 detected");
					res = stack.top() / last_top;
				}
				stack.pop();
				if (res < std::numeric_limits<int>::min() || res > std::numeric_limits<int>::max())
					throw std::invalid_argument("number overflow");
				stack.push(res);
			}
			i++;
			continue;
		} else {
			char *end;
			res = std::strtold(arg.c_str() + i, &end);
			if (res < std::numeric_limits<int>::min() || res > std::numeric_limits<int>::max())
				throw std::invalid_argument("number overflow");
			stack.push(res);
			i += end - (arg.c_str() + i);
		}
	}
	if (res < std::numeric_limits<int>::min() || res > std::numeric_limits<int>::max())
		throw std::invalid_argument("result overflow");
	return res;
}