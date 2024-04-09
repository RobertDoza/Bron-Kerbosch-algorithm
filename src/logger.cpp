#include <iostream>

#include "logger.hpp"

void Logger::log(const std::string &message) {
	std::cout << message << "\n";
}

