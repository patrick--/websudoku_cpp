#include <iostream>
#include "websudoku.h"

int main() {

	std::cout << "Downloading a new puzzle with an easy difficulty!" << "\n";

	Websudoku ws = Websudoku(Puzzle_difficulty::easy);

	ws.download_new_puzzle();

  	std::cout << "Displaying puzzle in console: " << "\n" << ws.to_str() << "\n";

  	std::cout << "Downloading a harder puzzle! " << "\n";

  	ws.download_new_puzzle(Puzzle_difficulty::evil);

  	std::cout << "Displaying puzzle in console: " << "\n" << ws.to_str() << "\n";

    std::cout << "Displaying puzzle in console with solution: " << "\n" << ws.to_str(true) << "\n";
 
 	std::cout << "Done!";
  return 0;
}