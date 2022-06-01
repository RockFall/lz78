#include "lz78.hpp"
#include "prefixtree.hpp"

#include <fstream>
#include <iostream>

void Lz78::Compress(std::string in_file, std::string out_file) {
  // Initialize the Suffix Tree we're
  // gonna use as our dictionary
  PrefixTree dict = PrefixTree();

  // Initialize pattern
  std::string pattern = "";

  // Starts inserting empty pattern
  dict.insert(pattern);

  // Reads the text file
  std::cout << "Reading input file" << std::endl;
  std::fstream is(in_file, std::ios::in | std::ios::binary);
  is.seekg(0, std::ios::end);
  size_t data_size = is.tellg();
  is.seekg(0, std::ios::beg);
  std::unique_ptr<char[]> data(new char[data_size]);
  is.read(data.get(), data_size);
  is.close();
  std::cout << "Finished reading file" << std::endl;

  // For each character in input
  std::cout << "Starting file compression" << std::endl;
  std::string finalResult = "";
  for (size_t i = 0; i < data_size; ++i)
  {
    char c = data[i];
    //
    if (dict.contains(pattern)) {
      pattern += c;
    } else {
      finalResult += "(" + std::to_string(dict.code_of(pattern)) + ", " + c + ")";
      dict.insert(pattern + c);
      pattern = "";
    }
  }
  finalResult += "(" + std::to_string(dict.code_of(pattern)) + ", " + "" + ")";
  std::cout << "Compression completed successfully" << std::endl;

  // Writes the result on file
  if (out_file == "")
    out_file = in_file.replace(in_file.size()-4, 4, ".z78");
  std::cout << "Writing output file {" << out_file << "}" << std::endl;
  std::ofstream out(out_file);
  out << finalResult;
  out.close();
  std::cout << "Finished writing file" << std::endl;
}
  // Takes a compressed file and decompress it
void Lz78::Decompress(std::string in_file, std::string out_file) {
  // Initialize the Suffix Tree we're
  // gonna use as our dictionary
  PrefixTree dict = PrefixTree();

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
