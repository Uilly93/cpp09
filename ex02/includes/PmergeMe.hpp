#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>

std::vector<int> fill_stack(int ac, char **av);
std::vector<std::pair<int, int> > create_pairs(std::vector<int> &stack);
void merge_sort(std::vector<std::pair<int, int> > &pairs, int left, int right);
void fill_jacobsthal_array(std::vector<int> &jacobsthalArray);
std::vector<int> final_stack(std::vector<std::pair<int, int> > &pairs);
void insert_jacobsthal(std::vector<int> &jacobsthalArray, std::vector<std::pair<int, int> > &pairs,
					   std::vector<int> &final);

#endif