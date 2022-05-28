#include "suffixtree.hpp"

SuffixTree::SuffixTree() {

}
SuffixTree::~SuffixTree() {

}

// Searchs the tree for given pattern, returning TRUE if found
bool SuffixTree::contains(const std::string pattern) {
  // If repeating last search, return stored value
  if (pattern == last_search.pattern){
    return last_search.code != -1;
  }
  int code = -1;



  this->last_search.update(pattern, code);
  return code != -1;
}

// Inserts given suffix into the tree
void SuffixTree::insert(const std::string suffix) {

}

// Returns the code associated with given pattern
// If given pattern is not found on the tree, -1 is returned
int SuffixTree::code_of(const std::string pattern) {
// If repeating last search, return stored value
  if (pattern == last_search.pattern){
    return last_search.code;
  }
  int code = -1;



  this->last_search.update(pattern, code);
  return code;
}

// Return a suffix in the tree associated with given code
std::string SuffixTree::get_by_code(const int code) {

}
