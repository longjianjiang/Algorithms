//
//  main.cpp
//  Algorithms
//
//  Created by longjianjiang on 2019/2/20.
//  Copyright © 2019 longjianjiang. All rights reserved.
//

#include <iostream>

#include "data_structures/stack.h"
#include "data_structures/queue.h"
#include "data_structures/circular_queue.h"
#include "data_structures/double_ended_queue.h"
#include "data_structures/blocking_queue.h"
#include "data_structures/doubly_linked_list.h"
#include "data_structures/binary_search_tree.h"
#include "data_structures/red_black_bst.h"
#include "data_structures/binary_indexed_tree.h"

#include "algorithms/bubble_sort.h"
#include "algorithms/selection_sort.h"
#include "algorithms/insertion_sort.h"
#include "algorithms/heap_sort.h"

using namespace jiang;

void unit_test_bit() {
    int nums1[] = {1, 2, 3, 4, 5};
    jiang::binary_indexed_tree<int> bit1{nums1, sizeof(nums1)/sizeof(nums1[0])};
    assert(bit1.get_sum_until(4) == 15);
    bit1.show();

    bit1.update(4, 7);
    bit1.show();
    assert(bit1.get_sum_until(4) == 17);

    assert(bit1.get_sum_range(1, 3) == 9);
}

int main() {
  unit_test_bit();
}
