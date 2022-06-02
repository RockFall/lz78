#pragma once

#include <string>

// Able to perform compression and decompression of files following
// the LZ78 method.
class Lz78 {
public:
  // Takes a text file and compress it
  //   If not given an out_file name, it will be
  //   replaced to {in_file}.z78
  static void Compress(std::string in_file, std::string out_file="");

  // Takes a compressed file and decompress it
  //   If not given an out_file name, it will be
  //   replaced to {in_file}.txt
  static void Decompress(std::string in_file, std::string out_file="");

private:
};
