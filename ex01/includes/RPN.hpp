#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include "colors.hpp"
#include <stack>

std::stack<int> fill_stack(std::string arg);
double calcules_loop(std::string arg, std::stack<int> stack);

#endif