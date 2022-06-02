#include <iostream>
#include <string>

#include "lz78.hpp"

int main(int argc, char *argv[]) {
  if (argc < 3 || argc == 4 || argc > 5) {
    std::cout << "lz78: invalid input" << std::endl;
    return 1;
  }

  // Takes input file argument
  std::string in_file = std::string(argv[2]);

  // Takes output file argument (if given)
  std::string out_file = "";
  if (argc == 5){
    out_file = std::string(argv[4]);
  }

  // Starts compressing or decompressing
  if (std::string(argv[1]) == "-c") {
    Lz78::Compress(in_file, out_file);
  }

  else if (std::string(argv[1]) == "-x") {
    Lz78::Decompress(in_file, out_file);
  }

  return 0;
}
