#include <cctype>
#include <cstdlib>
#include <iomanip>
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

void check_terminated(std::string arg) {
	for (size_t i = arg.size(); i > 0; i--) {
		if (arg[i] == '*' || arg[i] == '/' || arg[i] == '+' || arg[i] == '-')
			return;
		if (std::isdigit(arg[i]))
			throw std::invalid_argument("Error: argument terminated by digit");
	}
}

std::stack<long> fill_stack(std::string arg) {
	std::stack<long> stack;
	size_t i = 0;
	unsigned int signs = count_signs(arg);
	check_terminated(arg);
	for (; arg[i];) {
		if (arg[i] == '*' || arg[i] == '/' || (arg[i] == '+' && !std::isdigit(arg[i + 1])) ||
			(arg[i] == '-' && !std::isdigit(arg[i + 1])) || std::isspace(arg[i])) {
			if ((arg[i] == '*' || arg[i] == '/' || arg[i] == '+' || arg[i] == '-') &&
				stack.size() < 2) {
				throw std::invalid_argument("invalid sign1");
			} else if ((arg[i] == '*' || arg[i] == '/' || arg[i] == '+' || arg[i] == '-') &&
					   stack.size() < 1) {
			}
			i++;
			continue;
		}
		char *end;
		long value = std::strtold(arg.c_str() + i, &end);
		std::cout << value << std::endl;
		stack.push(value);
		i += end - (arg.c_str() + i);
	}
	// std::cout << "i = " << stack.size() << std::endl;
	// std::cout << "sign = " << signs << std::endl;
	if (signs != stack.size() - 1)
		throw std::invalid_argument("invalid sign2");
	return stack;
}

size_t find_first_operator(const std::string &str) {
	for (size_t i = 0; i < str.length(); ++i) {
		if ((str[i] == '+' || str[i] == '-') && (i == 0 || !std::isdigit(str[i - 1])) &&
			!std::isdigit(str[i + 1])) {
			return i;
		}
		if (str[i] == '*' || str[i] == '/') {
			return i;
		}
	}
	return std::string::npos;
}

long calcules_loop(std::string arg, std::stack<long> stack) {
	int i = 0;
	long res = stack.top();
	stack.pop();
	size_t pos = find_first_operator(arg);
	if (pos == std::string::npos)
		throw std::invalid_argument("no signs found");
	std::string signs = arg.substr(pos);
	std::cout << signs << std::endl;
	while (signs[i]) {
		while (signs[i] != '+' && signs[i] != '-' && signs[i] != '/' && signs[i] != '*')
			i++;
		if (signs[i] == '+')
			res = stack.top() + res;
		if (signs[i] == '-')
			res = stack.top() - res;
		if (signs[i] == '*')
			res = stack.top() * res;
		if (signs[i] == '/') {
			if (res == 0)
				throw std::invalid_argument("division by 0 detected");
			res = stack.top() / res;
		}
		stack.pop();
		i++;
	}
	return res;
}

int RPN(std::string arg) {
	std::stack<int> stack;
	int res;

	for (int i = 0; arg[i];) {
		if ((arg[i] == '+' && !std::isdigit(arg[i + 1])) ||
			(arg[i] == '-' && !std::isdigit(arg[i + 1])) || arg[i] == '*' || arg[i] == '/' ||
			std::isspace(arg[i])) {
			if (stack.size() > 1 &&
				(arg[i] == '+' || arg[i] == '-' || arg[i] == '/' || arg[i] == '*')) {
				int last_top = stack.top();
				stack.pop();
				if (arg[i] == '+') {
					res = stack.top() + last_top;
				}
				if (arg[i] == '-')
					res = stack.top() - last_top;
				if (arg[i] == '*')
					res = stack.top() * last_top;
				if (arg[i] == '/') {
					if (last_top == 0)
						throw std::invalid_argument("division by 0 detected");
					res = stack.top() / last_top;
				}
				stack.pop();
				stack.push(res);
			}
			i++;
			continue;
		} else {
			char *end;
			res = std::strtold(arg.c_str() + i, &end);
			stack.push(res);
			i += end - (arg.c_str() + i);
		}
	}
	// std::cout << std::fixed << std::setprecision(2) << "result is: " << res << std::endl;
	// std::cout << "***res = " << res << std::endl;
	return res;
}