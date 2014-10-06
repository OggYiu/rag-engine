#ifndef __GUI_IMAGE_H__
#define __GUI_IMAGE_H__

#include <vector>
#include "GUI_Base.h"
#include "Primitive.h"

class Texture;

class GUI_Image: public GUI_Base
{
public:
	GUI_Image( const int x, const int y, const std::string& imagePath );
	GUI_Image( const int x, const int y, Texture* const texture );
	GUI_Image( const int x, const int y, std::vector<Primitive*>& primitives );
	~GUI_Image();
};
#endif
