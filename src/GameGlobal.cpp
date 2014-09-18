#include "GameGlobal.h"
#include "Helper.h"
#include <assert.h>

// static GameGlobal* s_gameplayGlobal = nullptr;

GameGlobal::GameGlobal()
	: gridWidth_(0)
	, gridHeight_(0)
	, gridCountX_(0)
	, gridCountY_(0)	
{
}

GameGlobal::~GameGlobal()
{
}

GameGlobal& GameGlobal::getInstance()
{
	static GameGlobal s_gg;
	return s_gg;
	// if ( s_gameplayGlobal == nullptr )
	// {
	// 	s_gameplayGlobal = new GameGlobal();
	// }

	// return *s_gameplayGlobal;
}

// void GameGlobal::releaseInstance()
// {
// 	SAFE_RELEASE(s_gameplayGlobal);
// }

void GameGlobal::setGridSize(const int w, const int h)
{
	assert( ( w > 0 && h > 0 ) || "invalid width or height" );
	
	gridWidth_ = w;
	gridHeight_ = h;
	gridCountX_ = floor(kernel.getScreenWidth() / gridWidth_);
	gridCountY_ = floor(kernel.getScreenHeight() / gridHeight_);	
}
