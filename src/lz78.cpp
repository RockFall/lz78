#include "lz78.hpp"
#include "prefixtree.hpp"

#include <fstream>
#include <iostream>
#include <unordered_map>

void DisplayPercentage(int i, int data_size) {
  if (i == data_size/4)
      std::cout << "25%" << std::endl;
  else if (i == (data_size)/2)
      std::cout << "50%" << std::endl;
  else if (i == (data_size*3)/4)
      std::cout << "75%" << std::endl;
  else if (i == data_size-1)
      std::cout << "100%" << std::endl;
}

// -------------------- COMPRESSION --------------------

void Lz78::Compress(std::string in_file, std::string out_file) {
  // Initialize the Suffix Tree that we're
  // gonna use as our dictionary
  PrefixTree dict = PrefixTree();

  // Initialize pattern
  std::string pattern = "";

  // Starts inserting empty pattern
  dict.insert(pattern);

  // ----------- FILE READING -----------
  std::cout << "Reading input file" << std::endl;
  std::fstream is(in_file, std::ios::in | std::ios::binary);
  is.seekg(0, std::ios::end);
  size_t data_size = is.tellg();
  is.seekg(0, std::ios::beg);
  std::unique_ptr<char[]> data(new char[data_size]);
  is.read(data.get(), data_size);
  is.close();
  std::cout << "Finished reading file" << std::endl;

  // ----------- COMPRESSION BEGINS -----------
  // For each character in input
  //  If dictionaty contains the pattern + character
  //    assign pattern + char to the pattern
  //  Else
  //      write pattern's code and char on output file as (code, char),
  //      insert pattern+char into the dictionary and resets the pattern
  std::cout << "Starting file compression" << std::endl;
  std::string finalResult = "";
  for (size_t i = 0; i < data_size; ++i)
  {
    // Useful info for big compressions
    DisplayPercentage(i, data_size);

    char c = data[i];

    if (dict.contains(pattern + c)) {
      pattern += c;
    }
    else {
      finalResult += "(" + std::to_string(dict.code_of(pattern)) + "," + c + ")";
      dict.insert(pattern + c);
      pattern = "";
    }
  }
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

// -------------------- DECOMPRESSION --------------------

void Lz78::Decompress(std::string in_file, std::string out_file) {
  // For the decompression, all we need is to map the codes
  //    we find on the file to patterns
  // Due to the nature of the problem, the unordered_map
  //    give us O(1) for insertions and look-ups
  std::unordered_map<int, std::string> dict;

  // Initialize pattern
  std::string pattern = "";

  // Starts inserting empty pattern
  dict.emplace(0, pattern);

  // ----------- FILE READING -----------
  // Reads the input file
  std::cout << "Reading input file" << std::endl;
  std::fstream is(in_file, std::ios::in | std::ios::binary);
  is.seekg(0, std::ios::end);
  size_t data_size = is.tellg();
  is.seekg(0, std::ios::beg);
  std::unique_ptr<char[]> data(new char[data_size]);
  is.read(data.get(), data_size);
  is.close();
  std::cout << "Finished reading file" << std::endl;


  // ----------- DECOMPRESSION -----------
  std::cout << "Starting file decompression" << std::endl;
  std::string finalResult = "";
  int insertionIndex = 0;
  for (size_t i = 0; i < data_size; ++i) {
    if (data[i] == '('){
      ++i;
      // -- Reading New Pair --

      // Get the code
      std::string codeStr = "";
      while (data[i] != ',') {
        codeStr += data[i++];
      }

      // Eat comma
      i++;

      // Inserting into the dict

      int code = std::stoi(codeStr);
      pattern = dict.at(code);
      dict.emplace(++insertionIndex, pattern + data[i]);
      finalResult +=  pattern + data[i];
    }
  }
  //std::string pair = "(" + std::to_string(dict.code_of(pattern)) + ", " + "" + ")";
  std::cout << "Decompression completed successfully" << std::endl;

  // Writes the result on file
  if (out_file == "")
    out_file = in_file.replace(in_file.size()-4, 4, ".txt");
  std::cout << "Writing output file {" << out_file << "}" << std::endl;
  std::ofstream out(out_file);
  out << finalResult;
  out.close();
  std::cout << "Finished writing file" << std::endl;
}
