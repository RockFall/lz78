#pragma once

#include <string>
#include <unordered_map>
#include <memory>

// Encapsulation for a shared_ptr<>
// For making it prettier to look at all those std::shared_ptr<Node>'s
// Use:
//       Ptr<int> new_int_ptr = MakePtr<int>(4);
template<typename T>
using Ptr = std::shared_ptr<T>;
template<typename T, typename ... Args>
constexpr Ptr<T> MakePtr(Args&& ... args)
{
  return std::make_shared<T>(std::forward<Args>(args)...);
}

// -------------------------------------------------------------------------------------
// A compressed TRIE that stores all prefixes of given text
class PrefixTree {
public:
  // Constructor/Destructor
  PrefixTree();
  ~PrefixTree();

  // Inserts given prefix into the tree
  void insert(const std::string prefix);

  // Searchs the tree for given pattern, returning TRUE if found
  bool contains(const std::string pattern);

  // Returns the code associated with given pattern
  // Each code is given to
  int code_of(const std::string pattern);

  // Return a prefix in the tree associated with given code
  std::string get_by_code(const int code);

private:
  // ------  PRIVATE STRUCTURES  ------

  // Structure that stores the last search for optimizations
  struct LastSearch {
    LastSearch(std::string p="", int c=0) : pattern(p), code(c) {}
    void update(std::string p = "", int c = 0) { pattern = p; code = c; }
    std::string pattern;
    int code;
  };

  // Structure of a Node in the TRIE
  struct Node {
    std::unordered_map<char, Ptr<Node>> children;
    int prefixIdx = -1;
    bool isEnd = false;
  };

private:
// ------  PRIVATE FUNCTIONS  ------
  Ptr<Node> TrieSearch(const Ptr<Node> root, const std::string str);
  void TrieInsert(const std::string prefix);
  Ptr<Node> MakeNode();
  Ptr<Node> MakeNode(const int index);
  Ptr<Node> MakeNode(const int index, const bool isEnd);

  int edge_length(Ptr<Node> node);
  int walk_down(Ptr<Node> currNode);
  void extend(int position);

private:
  // ------  PRIVATE VARIABLES  ------
  LastSearch _last_search = LastSearch("", -1);
  Ptr<Node> _root = nullptr;
  int _lastIdx = -1;
};
