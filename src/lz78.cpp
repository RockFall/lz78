#include "lz78.hpp"
#include "suffixtree.hpp";

#include <fstream>
#include <iostream>

void Lz78::Compress(std::string in_file, std::string out_file) {
  // Initialize the Suffix Tree we're
  // gonna use as our dictionary
  SuffixTree dict = SuffixTree();

  // Initialize pattern
  std::string pattern = "";

  // Starts inserting empty pattern
  dict.insert(pattern);

  // Reads the text file, char per char
  std::ifstream in(in_file);
  char c;
  while (in.get(c)) {
    if (dict.contains(pattern)) {
      pattern += c;
    } else {
      std::string pair = "(" + std::to_string(dict.code_of(pattern)) + ", " + c + ")";
      std::cout << pair;
      dict.insert(pattern + c);
      pattern = "";
    }
  }
  std::string pair = "(" + std::to_string(dict.code_of(pattern)) + ", " + "" + ")";
  std::cout << pair;
}
  // Takes a compressed file and decompress it
void Lz78::Decompress(std::string in_file, std::string out_file) {
  // Initialize the Suffix Tree we're
  // gonna use as our dictionary
  SuffixTree dict = SuffixTree();

  // Initialize pattern
  std::string pattern = "";

  // Starts inserting empty pattern
  dict.insert(pattern);

  // Reads the text file, char per char
  std::ifstream in(in_file);
  char c;
  while (in.get(c)) {
    // Reading New Pair
    if (c == '('){
      // Get the code
      std::string codeStr = "";
      in.get(c);
      while (c != ',') {
        codeStr += c;
        in.get(c);
      }
      // Get character
      in.get(c);

      // Inserting into the dict
      pattern = dict.get_by_code(std::stoi(codeStr));
      dict.insert(pattern + c);
      std::string pair = "(" + pattern + ", " + c + ")";
    }
  }
  std::string pair = "(" + std::to_string(dict.code_of(pattern)) + ", " + "" + ")";
  std::cout << pair;
}
