#include <string>


class node : public std::string{

  public:
  node();

  int count;
  
  node *after;
  node *before;

  int pair_dup_count;
  int total_pairs;

  node *pair_tree_root;
  //node *pair_after;
  //node *pair_before;

  void build_pair_tree(node *tree, std::string pair_word);
};
