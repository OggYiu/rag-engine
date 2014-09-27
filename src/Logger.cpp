#include "Logger.h"

#include <sstream>
#include "Kernel.h"

static Logger s_instance;

Logger::Logger()
	: drawToScreen_( true )
{
}

Logger::~Logger()
{
}

void Logger::trace( const std::string& tag, const std::string& msg, const Uint32 color )
{
	std::stringstream ss;
	ss << "<" << tag << "> : \"" << msg << "\"";
	std::string str = ss.str();

	if ( !drawToScreen_ ) {
		std::cout << str << std::endl;
	} else {
		kernel.getInstance().addDebugMsg( str, color );
	}
}

void Logger::d( const std::string& tag, const std::string& msg )
{
	trace( tag, msg, 0xFF00FF00 );
}

void Logger::w( const std::string& tag, const std::string& msg )
{
	trace( tag, msg, 0xFFFFFF00 );
}

void Logger::e( const std::string& tag, const std::string& msg )
{
	trace( tag, msg, 0xFFFF0000 );
	assert( false );
}
	
Logger& Logger::getInstance()
{
	return s_instance;
}
