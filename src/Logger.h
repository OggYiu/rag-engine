#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <string>

class Logger
{
public:
	Logger();
	~Logger();

public:
	void d( const std::string& tag, const std::string& msg );
	
public:
	static Logger& getInstance();

private:
	bool drawToScreen_;
};
#define logger Logger::getInstance()

#endif
