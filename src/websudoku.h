#ifndef WEBSUDOKU_H
#define WEBSUDOKU_H

#include <string>
#include "httplib.h"

enum class Puzzle_difficulty { easy = 1, medium, hard, evil };

class Websudoku {

public:
	Websudoku();
	Websudoku(Puzzle_difficulty diff);

	void set_difficulty_level(Puzzle_difficulty diff);
	void download_new_puzzle();
	void download_new_puzzle(Puzzle_difficulty diff);
	void write_to_file(const std::string& f, bool include_solution);
	std::string to_str(bool include_solution = false);


private:
	std::string format_puzzle_str(bool use_mask = false);
	std::string difficulty_to_str();
	std::string api_request();
	std::tuple<std::string, std::string> parse_api_result(const std::string& res);

	httplib::Client api_client;
	std::string puzzle_raw_str {};
	std::string puzzle_mask {};
	std::string puzzle_solution {};
	Puzzle_difficulty diff_level {Puzzle_difficulty::easy};	
};

#endif