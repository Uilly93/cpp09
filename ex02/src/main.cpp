#include "../includes/PmergeMe.hpp"
#include <exception>
#include <iostream>
#include <vector>

int main(int ac, char **av) {
  try {
	if(ac < 3){
		std::cerr << "Error: you need at least 2 numbers" << std::endl;
		return 1;
	}
    std::vector<int> stack = fill_stack(ac, av);
    // for (std::vector<int>::iterator it = stack.begin(); it != stack.end(); it++)
    //   std::cout << *it << std::endl;
	std::vector<std::pair<int, int> > pairs = create_pairs(stack);
	for(std::vector<std::pair<int, int> >::iterator it = pairs.begin(); it != pairs.end(); it++){
		std::cout << it->first << " " << it->second << std::endl;
	}

  } catch (std::exception &e) {
	std::cout << e.what() << std::endl;
  }
}