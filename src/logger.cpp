#include <iostream>
#include <sstream>

#include "logger.hpp"

void Logger::log(const std::string &message) {
	std::cout << message << "\n";
}

void Logger::log(const std::string &message, const int &tab_depth) {
	std::cout << indentation(tab_depth) << message << "\n";
}

std::string Logger::indentation(const int &depth) {
	std::stringstream buffer;

	for (int i = 0; i < depth; i++) {
		buffer << "|\t";
	}
	
	return buffer.str();
}

