#include "Page_GfxTest.h"
#include "Graphics.h"
#include "Kernel.h"
#include "Entity_Emitter.h"

Page_GfxTest::Page_GfxTest()
{
}

Page_GfxTest::~Page_GfxTest()
{
}

void Page_GfxTest::update(const double dt)
{
	Page::update(dt);
}

void Page_GfxTest::resolved()
{
	Page::resolved();

	// graphics = new Graphics();
	// graphics->setColor(0xFF0000FF);
	// graphics->drawSolidRect(100, 100, 200, 200);

	// graphics->setColor(0xFFFF0000);
	// graphics->setAlpha(50);
	// graphics->drawSolidRect(20, 80, 150, 130);
	
	// for ( int i = 0; i < kernel.getScreenHeight(); ++i ) {
	// 	for ( int j = 0; j < kernel.getScreenWidth(); ++j ) {
	// 		float value = calculate(j, i);
	// 		value *= 255.0;
	// 		int v = round(value);
	// 		v %= 255;
	// 		graphics.setColor(v, v, v);
	// 		graphics.drawPixel(j, i);
	// 	}	
	// }
	// graphics.setColor(255, 0, 0);
	// graphics.moveTo(0, 0);
 	// graphics.lineTo(kernel.getScreenWidth() / 2, kernel.getScreenHeight() / 2);
	// graphics.lineTo(200, 200);	
	// graphics.drawPixel(10, 10);
	// graphics.drawPixel(100, 100);	
//	this->addChild(graphics);
}
