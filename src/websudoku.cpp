
#include <iostream>
#include <exception>
#include "websudoku.h"
#include "httplib.h"

const auto websudoku_url = "nine.websudoku.com";
const auto api_port = 80;

struct ApiParseResult { 
	std::string parsed_puzzle_str; 
	std::string parsed_puzzle_mask;
};
	
Websudoku::Websudoku() : api_client (websudoku_url, api_port)  { }

Websudoku::Websudoku(Puzzle_difficulty diff) 
	: api_client (websudoku_url, api_port), diff_level {diff} { }

void Websudoku::set_difficulty_level(Puzzle_difficulty diff) {
	diff_level = diff;
}

void Websudoku::download_new_puzzle() {
	struct ApiParseResult res = parse_api_result(api_request());
	puzzle_raw_str = res.parsed_puzzle_str;
	puzzle_mask = res.parsed_puzzle_mask;
}

void Websudoku::download_new_puzzle(Puzzle_difficulty temp_diff) {
	auto existing_diff = diff_level;

	diff_level = temp_diff;
	struct ApiParseResult res = parse_api_result(api_request());
	diff_level = existing_diff;
	puzzle_raw_str = res.parsed_puzzle_str;
	puzzle_mask = res.parsed_puzzle_mask;
}

void Websudoku::write_to_file(const std::string& f, bool with_solved) {
	
	std::string file_contents = format_puzzle_str(true);

	if (with_solved) {
		file_contents += format_puzzle_str(false);
	}

	std::ofstream out (f);

	if (!out) {
		throw std::runtime_error("Unable to write output to file!");
	}

	out << file_contents;
	
}

std::string Websudoku::to_str(bool with_solved) {
	return (with_solved ? format_puzzle_str(true) + format_puzzle_str() : format_puzzle_str(true));
}
	
std::string Websudoku::format_puzzle_str(bool use_mask) {
	
	std::string pretty_str;

	for (auto i = 0; i < puzzle_raw_str.length(); i++) {
		if (i!= 0 && i % 9 == 0) {
			pretty_str += "\n";
		}

		if (use_mask && puzzle_mask[i] == '1') {
			pretty_str += "- ";
		}

		else {
				pretty_str  += puzzle_raw_str[i];
				pretty_str += " ";
		}
		
	}

	pretty_str += "\n------------------\n";

	return pretty_str;
}


std::string Websudoku::difficulty_to_str() {
	std::string query_param;

	switch(diff_level) {
		case Puzzle_difficulty::easy: query_param = "1"; break;
		case Puzzle_difficulty::medium: query_param = "2"; break;
		case Puzzle_difficulty::hard: query_param = "3"; break;
	}

	return query_param;
}

std::string Websudoku::api_request() {
	const auto endpoint = "/?level=";
	auto path_with_params = endpoint + difficulty_to_str();

	auto res = api_client.Get(path_with_params.c_str());

	if (!res) {
		throw std::runtime_error("Error making API request!");
	}

	if (res->status != 200) {
		throw std::runtime_error("Websudoku bad response!");
	}

	return res->body;

}

struct ApiParseResult Websudoku::parse_api_result(const std::string& api_res) {

	const auto puzzle_search_str = "<INPUT NAME=cheat ID=\"cheat\" TYPE=hidden VALUE=\"";
	const auto mask_search_str = "<INPUT ID=\"editmask\" TYPE=hidden VALUE=\"";
	const auto str_extract_len = 81;

	size_t str_index = api_res.find(puzzle_search_str);

	if (str_index == std::string::npos) {
		throw std::runtime_error("Error parsing API response!");
	}

	std::string puzzle = api_res.substr(str_index + strlen(puzzle_search_str), str_extract_len);

	str_index = api_res.find(mask_search_str);

	if (str_index == std::string::npos) {
		throw std::runtime_error("Error parsing API response!");
	}

	std::string mask = api_res.substr(str_index + strlen(mask_search_str), str_extract_len);

	return ApiParseResult{puzzle, mask};

}