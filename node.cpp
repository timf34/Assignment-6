#include "node.hpp"

node::node(){
  count = 1;
  before=nullptr;
  after=nullptr;

  int pair_dup_count = 0;
  
  pair_tree_root=nullptr;
  pair_after=nullptr;
  pair_before=nullptr;
}

