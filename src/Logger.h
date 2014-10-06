#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <string>
#include <assert.h>
#include "SDL.h"

class Logger
{
public:
	Logger();
	~Logger();

public:
	void trace( const std::string& tag, const std::string& msg, const int line, const std::string& filename, const Uint32 color );
	
	inline void d( const std::string& tag, const std::string& msg, const int line = __LINE__, const std::string& filename = __FILE__ ) {
		trace( tag, msg, line, filename, 0xFF00FF00 );
	}

	inline void w( const std::string& tag, const std::string& msg, const int line = __LINE__, const std::string& filename = __FILE__ ) {
	trace( tag, msg, line, filename, 0xFFFFFF00 );
}
	inline void e( const std::string& tag, const std::string& msg, const int line = __LINE__, const std::string& filename = __FILE__ ) {
	trace( tag, msg, line, filename, 0xFFFF0000 );
	assert( false );
}
	
public:
	static Logger& getInstance();

private:
	bool drawToScreen_;
};
#define logger Logger::getInstance()

#endif
