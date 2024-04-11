#include <iostream>
#include <fstream>

#include "test.hpp"
#include "graph.hpp"
#include "solve.hpp"
#include "logger.hpp"

void test_graph(const std::string &graph_dir_name) {
	std::string input_filename = graph_dir_name + "/matrix.txt";
	std::string output_filename = graph_dir_name + "/results.txt";

	Graph g(input_filename);

	std::ofstream output_file(output_filename);
	if (!output_file.is_open()) {
		throw std::runtime_error("Failed to open file for writing: " + output_filename);
	}
	
	unsigned num_calls_basic = perform_algorithm(g, AlgType::BASIC);
	
	#ifdef LOG
	Logger::log("");
	#endif
	
	unsigned num_calls_pivot = perform_algorithm(g, AlgType::PIVOTING);
	
	#ifdef LOG
	Logger::log("");
	#endif
	
	unsigned num_calls_degen = perform_algorithm(g, AlgType::DEGEN_ORDERING);
	
	output_file << "Number of function calls:\n";
	output_file << "basic: " << std::to_string(num_calls_basic) << "\n";
	output_file << "pivot: " << std::to_string(num_calls_pivot) << "\n";
	output_file << "degen: " << std::to_string(num_calls_degen) << "\n";
}
