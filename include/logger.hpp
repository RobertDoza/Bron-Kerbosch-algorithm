#pragma once

#include <string>

class Logger {
	public:
		static void log(const std::string&);
		static void log(const std::string &message, const int &tab_depth);
		
		static std::string indentation(const int &depth);
	private:
		Logger();
		~Logger();
		Logger(const Logger&) = delete;
		Logger& operator= (const Logger&) = delete;	
};
