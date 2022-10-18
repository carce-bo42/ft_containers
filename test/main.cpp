#include "ft/vector.hpp"
#include "ft/stack.hpp"
#include "debug.hpp"
#include <vector>
#include <stdio.h>
#include <map>
#include <iostream>
#include "vector/vector_test.hpp"

#include "ft/RBT/red_black_tree.hpp"
#include "ft/RBT/red_black_tree_node.hpp"
#include "ft/utils/pair.hpp"

int Test_Error(int result, int line, const char* file) {
  std::cout << "ERROR at line " << line << " from test "
            << file << std::endl;
  return result;
}

int vector_test() {
  if (insert_point_single_test() != 0
      || insert_range_value_single_test() != 0
      || insert_range_iterators_single_test() != 0
      || erase_range_single_test() != 0
      || erase_pos_single_test() != 0)
  {
    return 1;
  }
  return 0;
}

class Example {

  public:

  Example(int a, int b)
  :
    i(a),
    j(b)
  {}
  ~Example() {
    i = 0;
    j = 0;
  }

  int i;
  int j;

  void print_numbers() {
    std::cout << "i = " << i
              << ", j = " << j
              << std::endl;
  }


};

int main() {
{
  int a = 4;
  std::vector<int> vec(10, a);

  printf("%lu \n", vec.capacity());
  printf("%lu \n", vec.size());

  vec.resize(123);

  printf("%lu \n", vec.capacity());
  printf("%lu \n", vec.size());
  //printf("%i \n", vec.front()); segfaultea.
}
  if (vector_test() != 0) {
    return 1;
  }
{
  std::allocator<Example> alloc;

  Example* ptr = alloc.allocate(1);

  // Correct way of calling construct with no simple constructor ?
  alloc.construct(ptr, Example(3, 4 ));

  ptr->print_numbers();

  alloc.destroy(ptr);
  ptr->print_numbers();

  alloc.deallocate(ptr, 1);

/*
 * With nodes:
 * 
 * alloc = std::allocator<Node>
 * node_ptr = alloc.allocate(1);
 * alloc.construct(node_ptr, rb_tree_node(a, b, c, d)); (works)
 * 
 * We recieve an std::pair<Key, T>. 
 * this std::pair is the value_type of the map.
 * The correct way of creating a node, will be:
 * node_ptr = node_allocator.allocate(1);
 * node_allocator.construct(node_ptr, rb_tree_node(pair, parent,
 *                                                 color, orientation)).
 * This should work.
 * 
 * 
 */
}
{
  ft::rb_tree<
    int,
    ft::pair<int, std::string>,
    get_key<int, ft::pair<int, std::string> > > tree;
  
  ft::rb_tree_node<ft::pair<int, std::string> > *node =
      tree.construct_node(ft::pair<int, std::string>(3, "hello"),
                          NULL, root, black);
  node->print_node_state();
  node->change_color();
  node->print_node_state();

  tree.pure_insert(node);
  std::cout << "minimum : " << tree.get_minimum() <<  std::endl;
  std::cout << "maximum : " << tree.get_maximum() <<  std::endl;

  std::map<int, std::string> map;

  map.insert(std::pair<int, std::string>(3, "hello)"));
  map.insert(std::pair<int, std::string>(5, "hello)"));

  std::map<int, std::string>::iterator it = map.begin();
  std::cout << it->first << std::endl;

}

  return 0;
}