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

void Logger::trace( const std::string& tag, const std::string& msg, const int line, const std::string& filename, const Uint32 color )
{
	std::stringstream ss;
	ss << "<" << tag << "> : \"" << msg << "\", line: " << line << ", file: " << filename;
	std::string str = ss.str();

	if ( !drawToScreen_ ) {
		std::cout << str << std::endl;
	} else {
		kernel.getInstance().addDebugMsg( str, color );
	}
}
	
Logger& Logger::getInstance()
{
	return s_instance;
}
