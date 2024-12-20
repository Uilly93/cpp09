#include "../includes/PmergeMe.hpp"
#include "../includes/colors.hpp"
#include <algorithm>
#include <ctime>
#include <deque>
#include <exception>
#include <iomanip>
#include <ios>
#include <iostream>
#include <vector>

int main(int ac, char **av) {
	try {
		if (ac < 2) {
			std::cerr << "Error: you need at least 2 numbers" << std::endl;
			return 1;
		}
		{
			std::cout << "--- PmergeMe with vector Array ---" << std::endl;
			std::vector<int> vec;
			fill_stack<std::vector<int> >(ac, av, vec);
			std::vector<int> vector_sorted;
			std::cout << "-------------------- Starting sort ---------------------------"
					  << std::endl;
			std::clock_t start = std::clock();
			PmergeMe<std::vector<int>, std::vector<std::pair<int, int> > >(vec, vector_sorted);
			std::clock_t end = std::clock();
			double duration = double(end - start) / CLOCKS_PER_SEC;
			std::cout << "Vector Array [" << vector_sorted.size() << "] sorted in " << std::fixed << std::setprecision(5) << duration
					  << " secondes" << std::endl;
			std::cout << "--------------------------------------------------------------"
					  << std::endl;

			// if (std::is_sorted(vector_sorted.begin(), vector_sorted.end()))
			// 	std::cout << NGREEN << "Vector array is sorted" << RESET << std::endl;
			// else
			// 	std::cout << NRED << "Vector array is NOT sorted" << RESET << std::endl;
		}
		{
			std::cout << "--- PmergeMe with deque Array ---" << std::endl;
			std::deque<int> deq;
			fill_stack<std::deque<int> >(ac, av, deq);
			std::deque<int> deque_sorted;
			std::cout << "-------------------- Starting sort ---------------------------"
					  << std::endl;
			std::clock_t start = std::clock();
			PmergeMe<std::deque<int>, std::deque<std::pair<int, int> > >(deq, deque_sorted);
			std::clock_t end = std::clock();
			double duration = double(end - start) / CLOCKS_PER_SEC;
			std::cout << "Deque Array [" << deque_sorted.size() << "] sorted in " << std::fixed << std::setprecision(5) << duration
					  << " secondes" << std::endl;
			std::cout << "--------------------------------------------------------------"
					  << std::endl;

			// for(std::deque<int>::iterator it = deque_sorted.begin(); it != deque_sorted.end();
			// it++) 	std::cout << *it << std::endl;

			// if (std::is_sorted(deque_sorted.begin(), deque_sorted.end())) // cant compile in cpp98
			// 	std::cout << NGREEN << "Deque array is sorted" << RESET << std::endl;
			// else
			// 	std::cout << NRED << "Deque array is NOT sorted" << RESET << std::endl;
		}
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}