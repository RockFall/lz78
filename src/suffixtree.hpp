#pragma once

#include <string>
#include <vector>
#include <memory>

// For making it prettier to look at all those std::shared_ptr<T>
// Use:
//       Ptr<int> new_int_ptr = MakePtr<int>(4);
template<typename T>
using Ptr = std::shared_ptr<T>;
template<typename T, typename ... Args>
constexpr Ptr<T> MakePtr(Args&& ... args)
{
  return std::make_shared<T>(std::forward<Args>(args)...);
}

// A compressed TRIE that stores all suffixes of given text
class SuffixTree {
public:
  // Constructor/Destructor
  SuffixTree();
  ~SuffixTree();

  // Inserts given suffix into the tree
  void insert(const std::string suffix);

  // Searchs the tree for given pattern, returning TRUE if found
  bool contains(const std::string pattern);

  // Returns the code associated with given pattern
  int code_of(const std::string pattern);

  // Return a suffix in the tree associated with given code
  std::string get_by_code(const int code);

private:
  struct LastSearch {
    LastSearch(std::string p="", int c=0) : pattern(p), code(c) {}
    void update(std::string p = "", int c = 0) { pattern = p; code = c; }
    std::string pattern;
    int code;
  };

  LastSearch last_search = LastSearch("", 0);



  struct Node {
    std::vector<Ptr<Node>> children;
    Ptr<Node> suffixLink;

    int start;
    Ptr<int> end;

    int suffixIdx;
  };

  Ptr<Node> new_node(int start, Ptr<int> end);
  int edge_length(Ptr<Node> node);
  int walk_down(Ptr<Node> currNode);
  void extend(int position);
};
