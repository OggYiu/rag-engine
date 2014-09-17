#ifndef __GUI_IMAGE_H__
#define __GUI_IMAGE_H__

#include <string>
#include "GUI_Base.h"

class GUI_Image: public GUI_Base
{
public:
	GUI_Image(const float x, const float y, const std::string& path );
	~GUI_Image();
};
#endif
