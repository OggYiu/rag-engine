#include "Page_Gameplay.h"

#include "GameGlobal.h"
#include "Graphics.h"
#include "Helper.h"
#include "Entity_Emitter.h"
#include <limits>

Page_Gameplay::Page_Gameplay()
	: mapCanvas_(nullptr)
{
}

Page_Gameplay::~Page_Gameplay()
{
//	std::cout << "page gameplay decon" << std::endl;
}	

void Page_Gameplay::enter()
{
	Parent::enter();
}

void Page_Gameplay::update(const double dt)
{
//	std::cout << "page game play update started " << std::endl;
//	Page::update(dt);
	
	Parent::update(dt);

//	std::cout << "page game play update started " << std::endl;
	mapCanvas_->clear();

	float v = 0.0f;
	float minValue = std::numeric_limits<float>::max();
	float maxValue = std::numeric_limits<float>::min();	
	
	// for ( int j = 0; j < kernel.getScreenHeight(); ++j )
	int drawPosX = 0;
	int drawPosY = 0;
	int valuePosX = 0;
	int valuePosY = 0;	
	for ( int j = 0; j < gg.getGridCountY(); ++j )		
	{
		// for ( int i = 0; i < kernel.getScreenWidth(); ++i )
		for ( int i = 0; i < gg.getGridCountX(); ++i )			
		{
			values_[j][i] = v = 0;
			drawPosX = i * gg.getGridWidth(); drawPosY = j * gg.getGridHeight();			valuePosX = round(drawPosX + gg.getGridWidth() / 2);
			valuePosY = round(drawPosY + gg.getGridHeight() / 2);
			
			for ( int m = 0; m < (int)emitters_.size(); ++m )
			{
//				v += emitters_[m]->calculate(i, j) * 255;
				// v += emitters_[m]->calculate(valuePosX, valuePosY) * 255;
				values_[j][i] += emitters_[m]->calculate(valuePosX, valuePosY) * 255;
			}
			
			v = values_[j][i];
//			std::cout << "v1: " << v << ", " << maxValue << ", " << minValue << std::endl;
			if ( v > maxValue ) {
				maxValue = v;
			} else if ( v < minValue ) {
				minValue = v;
			}
			
//			std::cout << "v2: " << v << ", " << maxValue << ", " << minValue << std::endl;			
		}
	}

//	std::cout << "limits: " << maxValue << ", " << minValue << std::endl;
//	maxValue -= minValue;
//	minValue = 0;
	for ( int j = 0; j < gg.getGridCountY(); ++j )		
	{
		for ( int i = 0; i < gg.getGridCountX(); ++i )			
		{
			drawPosX = i * gg.getGridWidth(); drawPosY = j * gg.getGridHeight();
			//float v1 = values_[j][i] - minValue;
			//float v2 = v1 / maxValue;
			float v2 = values_[j][i];
			v = easeOutQuart(v2-minValue, minValue, maxValue - minValue, maxValue-minValue);
			v = easeOutQuart(v-minValue, minValue, maxValue - minValue, maxValue-minValue);			
//			v = linearTween(v2-minValue, minValue, maxValue, maxValue+minValue)
			v /= maxValue;
//			v *= 255;
//			v = round(v);

//			std::cout << "v: " << v << std::endl;
//			mapCanvas_->setColor(v, v, v , 255);
//			mapCanvas_->setColor(0xFF000000 + 0x00FF0000 * v);
			int r = 0;
			int g = 0;
			int b = 0;
			if ( v < ((1.0f / 3.0f) * 1) ) {
				v /= (1.0f / 3.0f);
				r = round(v * 255.0f);
			} else if ( v < ((1.0f / 3.0f) * 2) ) {
				r = 255;
				v -= ((1.0f / 3.0f) * 1);
				v /= (1.0f / 3.0f);				
				g = round(v * 255.0f);
			} else if ( v < ((1.0f / 3.0f) * 3)) {
				r = 255;
				g = 255;
				v -= ((1.0f / 3.0f) * 2);
				v /= (1.0f / 3.0f);
				b = round(v * 255.0f);				
			}
//			mapCanvas_->setColor(0xFF000000 + (((int)round(0xFFFFFF * v))));
			mapCanvas_->setDrawColor( r, g, b, 100 );
			mapCanvas_->drawSolidRect(drawPosX, drawPosY, gg.getGridWidth(), gg.getGridHeight());
		}
	}
}

bool Page_Gameplay::resolved()
{
	Parent::resolved();

	// float min = 10.0f;
	// float max = 100.0f;	
	// for ( int i = 0; i < 10; ++i ) {
	// 	std::cout << easeOutQuart(i / 10.0f, min, max - min, 1) << std::endl;
	// }
	
	gg.setGridSize(8, 8);	
	for ( int j = 0; j < gg.getGridCountY(); ++j )		
	{
		std::vector<float> vec;
		for ( int i = 0; i < gg.getGridCountX(); ++i )			
		{
			vec.push_back(0.0f);
		}
		values_.push_back(vec);		
	}


	// for ( int i = 0; i < gg.getGridCountY(); ++i )
	// {
	// 	for ( int j = 0; j < gg.getGridCountX(); ++j )
	// 	{
	// 	}
	// }
	mapCanvas_ = new Graphics();
	this->addChild(mapCanvas_);

	{
		Entity_Emitter* emitter = new Entity_Emitter(120, 60, 100.0f);
		emitters_.push_back(emitter);
		this->addChild(emitter);
	}

	{
		Entity_Emitter* emitter = new Entity_Emitter(150, 100, 80.0f);
		emitters_.push_back(emitter);
		this->addChild(emitter);
	}

	return true;
}
