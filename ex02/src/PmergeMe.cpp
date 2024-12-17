#include <cstdlib>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <utility>
#include <vector>

std::vector<int> fill_stack(int ac, char **av) {
  std::vector<int> stack;
  for (int i = 1; i < ac; i++) {
    char *end;
    int value = std::strtold(av[i], &end);
    if (*end != 0)
      throw std::invalid_argument("invalid number");
    if (value > std::numeric_limits<int>::max() || value < 0)
      throw std::invalid_argument("Overflow or negative number");
    stack.push_back(value);
  }
  return stack;
}


void sort_pairs(std::vector<std::pair<int, int> > &pairs) {
	std::vector<std::pair<int, int> >::iterator it = pairs.begin();
	for (; it != pairs.end(); it++) {
		if (it->second > it->first)
			std::swap(it->second, it->first);
	}
}

std::vector<std::pair<int, int> > create_pairs(std::vector<int> &stack) {
  std::vector<std::pair<int, int> > pairs;
  for (std::vector<int>::iterator it = stack.begin(); it != stack.end(); it++) {
    if (it + 1 != stack.end()) {
      pairs.push_back(std::make_pair(*it, *(it + 1)));
      it++;
    }
  }
  sort_pairs(pairs);
  return pairs;
}

// void merge(std::vector<int> &stack, int left, int mid, int end) {
//   int n1 = mid - left + 1;
//   int n2 = end - mid;

//   std::vector<std::pair<int, int> > lside(n1);
//   std::vector<std::pair<int, int> > rside(n2);
// }
