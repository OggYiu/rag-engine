#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <string>
#include "SDL.h"

class Logger
{
public:
	Logger();
	~Logger();

public:
	void trace( const std::string& tag, const std::string& msg, const Uint32 color );
	void d( const std::string& tag, const std::string& msg );
	void w( const std::string& tag, const std::string& msg );
	void e( const std::string& tag, const std::string& msg );	
	
public:
	static Logger& getInstance();

private:
	bool drawToScreen_;
};
#define logger Logger::getInstance()

#endif
