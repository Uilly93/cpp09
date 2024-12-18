#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <utility>
#include <vector>

void check_duplicate(std::vector<int> &stack) {
	for (std::vector<int>::iterator it = stack.begin(); it != stack.end(); ++it) {
		for (std::vector<int>::iterator it2 = it + 1; it2 != stack.end(); ++it2) {
			if (*it == *it2) {
				throw std::invalid_argument("Duplicate number found");
			}
		}
	}
}

std::vector<int> fill_stack(int ac, char **av) {
	std::vector<int> stack;
	for (int i = 1; i < ac; i++) {
		char *end;
		int value = std::strtold(av[i], &end);
		if (*end != 0)
			throw std::invalid_argument("invalid number found");
		if (value > std::numeric_limits<int>::max() || value < 0)
			throw std::invalid_argument("Overflow or negative number found");
		stack.push_back(value);
	}
	check_duplicate(stack);
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
			if (*it > *(it + 1))
				pairs.push_back(std::make_pair(*it, *(it + 1)));
			else
				pairs.push_back(std::make_pair(*(it + 1), *it));
			it++;
		}
	}
	sort_pairs(pairs);
	return pairs;
}

void merge(std::vector<std::pair<int, int> > &pairs, int left, int mid, int right) {
	int n1 = mid - left + 1;
	int n2 = right - mid;
	std::vector<std::pair<int, int> > L(n1), R(n2);
	for (int i = 0; i < n1; i++)
		L[i] = pairs[left + i];
	for (int j = 0; j < n2; j++)
		R[j] = pairs[mid + 1 + j];

	int i = 0, j = 0;
	int k = left;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			pairs[k] = L[i];
			i++;
		} else {
			pairs[k] = R[j];
			j++;
		}
		k++;
	}
	while (i < n1) {
		pairs[k] = L[i];
		i++;
		k++;
	}
	while (j < n2) {
		pairs[k] = R[j];
		j++;
		k++;
	}
}

void merge_sort(std::vector<std::pair<int, int> > &pairs, int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;

		std::vector<std::pair<int, int> > l_side(pairs.begin(), pairs.begin() + mid);
		std::vector<std::pair<int, int> > r_side(pairs.begin() + mid, pairs.end());

		merge_sort(pairs, left, mid);
		merge_sort(pairs, mid + 1, right);

		merge(pairs, left, mid, right);
	}
}

std::vector<int> final_stack(std::vector<std::pair<int, int> > &pairs) {
	std::vector<int> final;
	for (size_t i = 0; i < pairs.size(); i++) {
		final.push_back(pairs[i].first);
	}
	return final;
}

void fill_jacobsthal_array(std::vector<int> &jacobsthalArray) {
	int size = jacobsthalArray.size();

	if (size > 0)
		jacobsthalArray[0] = 3;
	if (size > 1)
		jacobsthalArray[1] = 5;
	for (int i = 2; i < size; i++) {
		jacobsthalArray[i] = jacobsthalArray[i - 1] + 2 * jacobsthalArray[i - 2];
	}
}

bool compare_with_jacobsthal(std::vector<int> &jacobsthalArray, int vec_index) {
	for (size_t i = 0; i < jacobsthalArray.size(); i++) {
		if (vec_index == jacobsthalArray[i])
			return true;
	}
	return (false);
}

void insert_jacobsthal(std::vector<int> &jacobsthalArray, std::vector<std::pair<int, int> > &pairs,
					   std::vector<int> &final) {
	size_t j_index = 0;
	size_t vec_index = 1;
	while (vec_index < pairs.size() && (size_t)jacobsthalArray[j_index] < pairs.size()) {
		final.push_back(pairs[jacobsthalArray[j_index]].second);
		std::cout << "added (j) [" << jacobsthalArray[j_index]
				  << "] = " << pairs[jacobsthalArray[j_index]].second << std::endl;
		if (compare_with_jacobsthal(jacobsthalArray, vec_index))
			vec_index++;
		else {
			final.push_back(pairs[vec_index].second);
			std::cout << "added [" << vec_index
					  << "] = " << pairs[vec_index].second << std::endl;
		}
		j_index++;
		vec_index++;
	}
}
