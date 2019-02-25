//
//  main.cpp
//  Algorithms
//
//  Created by longjianjiang on 2019/2/20.
//  Copyright © 2019 longjianjiang. All rights reserved.
//

#include <iostream>

#include "data_structures/doubly_linked_list.h"
#include "data_structures/binary_search_tree.h"
#include "data_structures/red_black_bst.h"

#include "algorithms/bubble_sort.h"
#include "algorithms/selection_sort.h"
#include "algorithms/insertion_sort.h"
#include "algorithms/heap_sort.h"

using namespace jiang;

int main() {
  std::cout << "Testing binary search tree<int>" << std::endl;

  std::cout << "Testing red black bst<int>" << std::endl;

  std::vector<int> v = {1, 5, 2, 7, 3};
  for (auto num: v) {
  	std::cout << num << " ";
  }
  std::cout << "==================\n";


  heap_sort<int>(v);
  for (auto num: v) {
  	std::cout << num << " ";
  }
  std::cout << "==================\n";

  heap_sort<int>(v, false);
  for (auto num: v) {
  	std::cout << num << " ";
  }
  std::cout << "==================\n";

  doubly_linked_list<int> head = doubly_linked_list<int>();
  head.insert(2);
  head.insert(1);
  head.insert(3);
  head.insert(5);
  head.insert(4);

  head.show();
  head.bubble_sort_list();
  head.show();
}
