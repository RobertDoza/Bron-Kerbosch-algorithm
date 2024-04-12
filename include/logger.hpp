#pragma once

// #define LOG

#include <string>

class Logger {
	public:
		// Function logs given string to output.
		static void log(const std::string&);
		
		// Function logs given string to output, with provided tab depth.
		static void log(const std::string&, const int&);
		
		// Function creates an indentation with the provided tab depth.
		static std::string indentation(const int&);
	private:
		// Private constructor to prevent instantiation.
		Logger();
		
		// Private destructor to prevent instantiation.
		~Logger();
		
		// Deleted copy constructor to prevent instantiation.
		Logger(const Logger&) = delete;
		
		// Deleted assignment operator to prevent instantiation.
		Logger& operator= (const Logger&) = delete;	
};
