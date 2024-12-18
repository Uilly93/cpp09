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

	// start count time;
    std::vector<int> stack = fill_stack(ac, av);
	std::vector<std::pair<int, int> > pairs = create_pairs(stack);
	// for(std::vector<std::pair<int, int> >::iterator it = pairs.begin(); it != pairs.end(); it++){
	// 	std::cout << it->first << " " << it->second << std::endl;
	// }

    merge_sort(pairs, 0, pairs.size() - 1);
	std::cout << "--------------------------------------------------------------" << std::endl;
	for(std::vector<std::pair<int, int> >::iterator it = pairs.begin(); it != pairs.end(); it++){
		std::cout << it->first << " " << it->second << std::endl;
	}
	std::cout << "--------------------------------------------------------------" << std::endl;
	std::vector<int> jacobsthalArray(stack.size() / 2);
    fill_jacobsthal_array(jacobsthalArray);
    // for (size_t i = 0; i < stack.size() / 2; i++) {
    //     std::cout << "J[" << i << "] = " << jacobsthalArray[i] << std::endl;
    // }
	std::vector<int> final = final_stack(pairs);
	insert_jacobsthal(jacobsthalArray, pairs, final);
	for (size_t i = 0; i < final.size(); i++) {
        std::cout << "[" << i << "] = " << final[i] << std::endl;
    }
  } catch (std::exception &e) {
	std::cout << e.what() << std::endl;
  }
}
// int main(int ac, char **av) {
//   try {
//     if (ac < 3) {
//       std::cerr << "Error: you need at least 2 numbers" << std::endl;
//       return 1;
//     }

//     // Remplir le vecteur avec les arguments de la ligne de commande
//     std::vector<int> stack = fill_stack(ac, av);

//     // Créer des paires à partir du vecteur
//     std::vector<std::pair<int, int> > pairs = create_pairs(stack);

//     // Afficher les paires
//     std::cout << "Pairs:" << std::endl;
//     for (std::vector<std::pair<int, int> >::iterator it = pairs.begin(); it != pairs.end(); ++it) {
//       std::cout << "(" << it->first << ", " << it->second << ")" << std::endl;
//     }

//     // Trier le vecteur en utilisant merge sort
//     merge_sort(pairs, 0, pairs.size() - 1);

//     // Afficher le vecteur trié
//     std::cout << "Sorted stack:" << std::endl;
//     for (std::vector<int>::iterator it = stack.begin(); it != stack.end(); ++it) {
//       std::cout << *it << " ";
//     }
//     std::cout << std::endl;

//   } catch (std::exception &e) {
//     std::cerr << "Exception: " << e.what() << std::endl;
//     return 1;
//   }

//   return 0;
// }