#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>

std::vector<int> fill_stack(int ac, char **av);
std::vector<std::pair<int, int> > create_pairs(std::vector<int> &stack);

#endif