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
		// {
		// 	std::vector<int> vec;
		// 	fill_stack(ac, av, vec);
		// 	std::clock_t start = std::clock();
		// 	std::sort(vec.begin(), vec.end());
		// 	std::clock_t end = std::clock();
		// 	double duration = double(end - start) / CLOCKS_PER_SEC;
		// 	std::cout << PURPLE << "Vector Array sorted in " << std::fixed
		// 			  << std::setprecision(7) << duration << " secondes using std::sort" << RESET << std::endl;
		// }
		{
			std::cout << NBLUE << "--- PmergeMe with vector Array ---" << RESET << std::endl;
			std::vector<int> vec;
			fill_stack<std::vector<int> >(ac, av, vec);

			std::cout << RED << "--- Raw vector Array ---" << RESET << std::endl;
			for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
				std::cout << NRED << "[" << *it << "]";
			std::cout << RESET << std::endl;

			std::vector<int> vector_sorted;
			std::cout << "-------------------- Starting sort ---------------------------"
					  << std::endl;
			std::clock_t start = std::clock();
			PmergeMe<std::vector<int>, std::vector<std::pair<int, int> > >(vec, vector_sorted);
			std::clock_t end = std::clock();
			double duration = double(end - start) / CLOCKS_PER_SEC;
			std::cout << "Vector Array [" << vector_sorted.size() << "] sorted in " << std::fixed
					  << std::setprecision(7) << duration << " secondes" << std::endl;
			std::cout << "--------------------------------------------------------------"
					  << std::endl;

			std::cout << GREEN << "--- Sorted vector Array ---" << RESET << std::endl;
			for (std::vector<int>::iterator it = vector_sorted.begin(); it != vector_sorted.end();
				 it++)
				std::cout << NGREEN << "[" << *it << "]";
			std::cout << RESET << std::endl;

			// if (std::is_sorted(vector_sorted.begin(), vector_sorted.end()))
			// 	std::cout << NGREEN << "Vector array is sorted" << RESET << std::endl;
			// else
			// 	std::cout << NRED << "Vector array is NOT sorted" << RESET << std::endl;
		}
		{
			std::cout << std::endl
					  << NBLUE << "--- PmergeMe with deque Array ---" << RESET << std::endl;
			std::deque<int> deq;
			fill_stack<std::deque<int> >(ac, av, deq);

			std::cout << RED << "--- Raw deque Array ---" << RESET << std::endl;
			for (std::deque<int>::iterator it = deq.begin(); it != deq.end(); it++)
				std::cout << NRED << "[" << *it << "]";
			std::cout << RESET << std::endl;

			std::deque<int> deque_sorted;
			std::cout << "-------------------- Starting sort ---------------------------"
					  << std::endl;
			std::clock_t start = std::clock();
			PmergeMe<std::deque<int>, std::deque<std::pair<int, int> > >(deq, deque_sorted);
			std::clock_t end = std::clock();
			double duration = double(end - start) / CLOCKS_PER_SEC;
			std::cout << "Deque Array [" << deque_sorted.size() << "] sorted in " << std::fixed
					  << std::setprecision(7) << duration << " secondes" << std::endl;
			std::cout << "--------------------------------------------------------------"
					  << std::endl;

			std::cout << GREEN << "--- Sorted deque Array ---" << RESET << std::endl;
			for (std::deque<int>::iterator it = deque_sorted.begin(); it != deque_sorted.end();
				 it++)
				std::cout << NGREEN << "[" << *it << "]";
			std::cout << RESET << std::endl;

			// if (std::is_sorted(deque_sorted.begin(), deque_sorted.end()))
			// 	std::cout << NGREEN << "Deque array is sorted" << RESET << std::endl;
			// else
			// 	std::cout << NRED << "Deque array is NOT sorted" << RESET << std::endl;
		}
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}