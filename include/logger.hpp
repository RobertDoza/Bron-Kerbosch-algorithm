#pragma once

#include <string>

class Logger {
	public:
		static void log(const std::string&);
	private:
		Logger();
		~Logger();
		Logger(const Logger&) = delete;
		Logger& operator= (const Logger&) = delete;	
};
