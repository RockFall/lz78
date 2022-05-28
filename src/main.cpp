#include <iostream>
#include <string>

#include "lz78.hpp"

int main(int argc, char *argv[]) {

  // Takes input file argument
  std::string in_file = std::string(argv[2]);

  std::string out_file = "";
  // Takes output file argument (if given)
  if (argc == 5){
    out_file = std::string(argv[3]);
  }

  // Starts compressing or decompressing
  if (std::string(argv[1]) == "-c")
    Lz78::Compress(in_file, out_file);

  else if (std::string(argv[1]) == "-x")
    Lz78::Decompress(in_file, out_file);

  return 0;
}
