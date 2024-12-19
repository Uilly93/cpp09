#include "../includes/PmergeMe.hpp"
#include <algorithm>
#include <deque>
#include <exception>
#include <iostream>
#include <vector>

int main(int ac, char **av) {
	try {
		if (ac < 3) {
			std::cerr << "Error: you need at least 2 numbers" << std::endl;
			return 1;
		}
		{
			std::cout << "--- PmergeMe with vector Array ---" << std::endl;
			std::vector<int> vec;
			fill_stack<std::vector<int> >(ac, av, vec);
			std::vector<int> vector_sorted(vec.size());
			PmergeMe<std::vector<int>, std::vector<std::pair<int, int> > >(vec, vector_sorted);

			// if (std::is_sorted(vector_sorted.begin(), vector_sorted.end()))
			// 	std::cout << "vector array is sorted" << std::endl;
			// else
			// 	std::cout << "vector array is NOT sorted" << std::endl;
		}
		{
			std::cout << "--- PmergeMe with deque Array ---" << std::endl;
			std::deque<int> deq;
			fill_stack<std::deque<int> >(ac, av, deq);
			std::deque<int> deque_sorted;
			PmergeMe<std::deque<int>, std::deque<std::pair<int, int> > >(deq, deque_sorted);

			// for(std::deque<int>::iterator it = deque_sorted.begin(); it != deque_sorted.end(); it++)
			// 	std::cout << *it << std::endl;

			// if (std::is_sorted(deque_sorted.begin(), deque_sorted.end())) // cant compile in cpp98
			// 	std::cout << "deque array is sorted" << std::endl;
			// else
			// 	std::cout << "deque array is NOT sorted" << std::endl;
		}
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}