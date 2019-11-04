#include <iostream>
#include "websudoku.h"

int main() {
  //std::cout << "Main launched!!" << std::endl;
  //std::cout << "Using external resource httplib to make a get request..." << std::endl;
  
  Websudoku ws = Websudoku(Puzzle_difficulty::easy);
  ws.download_new_puzzle();
  //std::string test123 = ws.to_str(true);
  std::cout << ws.to_str(true);


  return 0;
}