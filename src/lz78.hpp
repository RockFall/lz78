#pragma once

#include <string>

class Lz78 {
public:
  // Takes a text file and compress it
  static void Compress(std::string in_file, std::string out_file="");
  // Takes a compressed file and decompress it
  static void Decompress(std::string in_file, std::string out_file="");

private:
};
