#include "prefixtree.hpp"

PrefixTree::PrefixTree()  {

}
PrefixTree::~PrefixTree() {

}

// Searchs the tree for given pattern, returning TRUE if found
bool PrefixTree::contains(const std::string pattern) {
  // If repeating last search, return stored value
  if (pattern == _last_search.pattern){
    return _last_search.code != -1;
  }
  int code = -1;

  Ptr<Node> found = TrieSearch(_root, pattern);
  if (found->isEnd)
    code = found->prefixIdx;

  this->_last_search.update(pattern, code);
  return code != -1;
}

// Inserts given prefix into the tree
void PrefixTree::insert(const std::string prefix) {
  TrieInsert(prefix);
}

// Returns the code associated with given pattern
// If given pattern is not found on the tree, -1 is returned
int PrefixTree::code_of(const std::string pattern) {
// If repeating last search, return stored value
  if (pattern == _last_search.pattern){
    return _last_search.code;
  }
  int code = -1;

  Ptr<Node> found = TrieSearch(_root, pattern);
  if (found->isEnd)
    code = found->prefixIdx;

  this->_last_search.update(pattern, code);
  return code;
}

// Return a prefix in the tree associated with given code
std::string PrefixTree::get_by_code(const int code) {
  return "NOT IMPLEMENTED";
}

Ptr<PrefixTree::Node> PrefixTree::TrieSearch(const Ptr<Node> begin, const std::string str) {
  if (begin == nullptr) {
    return nullptr;
  }

  if (str == "") {
    if (begin->children.find('\0') == begin->children.end())
      return nullptr;
    return begin->children.at('\0');
  }

  // Variable that will iterate down the tree
  Ptr<Node> explore = begin;

  // If some character on string is not found, return nullptr
  for (auto& ch : str) {
    if (explore->children.find(ch) == explore->children.end()) {
      return nullptr;
    }

    // Search down
    explore = explore->children.at(ch);
  }

  // Returns the last node found for given string
  return explore;
}

void PrefixTree::TrieInsert(const std::string str) {
  if (_root == nullptr) {
    _root = MakeNode();
  }

  if (str == "") {
    _lastIdx++;
    _root->children['\0'] = MakeNode(_lastIdx, true);
    return;
  }

  // Variable that will iterate down the tree
  Ptr<Node> explore = _root;
  for (auto& ch : str) {
    // If character's not been found, create a node for it
    if (explore->children.find(ch) == explore->children.end()){
      _lastIdx++;
      explore->children[ch] = MakeNode(_lastIdx);
    }
    // Search down
    explore = explore->children.at(ch);
  }
  // Marks this node as an EndOfWord
  explore->isEnd = true;
}

Ptr<PrefixTree::Node> PrefixTree::MakeNode() {
  return MakePtr<Node>();
}

Ptr<PrefixTree::Node> PrefixTree::MakeNode(const int index) {
  Ptr<Node> newNode = MakePtr<Node>();
  newNode->prefixIdx = index;
  return newNode;
}

Ptr<PrefixTree::Node> PrefixTree::MakeNode(const int index, const bool isEnd) {
  Ptr<Node> newNode = MakePtr<Node>();
  newNode->prefixIdx = index;
  newNode->isEnd = isEnd;
  return newNode;
}
