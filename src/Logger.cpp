#include "Logger.h"

#include <sstream>
#include "Kernel.h"

static Logger s_instance;

Logger::Logger()
	: drawToScreen_( false )
{
}

Logger::~Logger()
{
}

void Logger::d( const std::string& tag, const std::string& msg )
{
	std::stringstream ss;
	ss << "<" << tag << "> : \"" << msg << "\"";
	std::string str = ss.str();

	if ( !drawToScreen_ ) {
		std::cout << str << std::endl;
	} else {
		// kernel.getInstance().addDebugMsg( str );
	}
}
	
Logger& Logger::getInstance()
{
	return s_instance;
}
