#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include "colors.hpp"
#include <stack>

std::stack<long> fill_stack(std::string arg);
long calcules_loop(std::string arg, std::stack<long> stack);

#endif