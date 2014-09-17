#ifndef __GAME_GLOBAL_H__
#define __GAME_GLOBAL_H__

class GameGlobal
{
public:
	static const int GRID_WIDTH = 32;
	static const int GRID_HEIGHT = 24;
	
public:
	GameGlobal();
	~GameGlobal();
	
public:
	static GameGlobal& getInstance();
	// static void releaseInstance();
	int getGridWidth() const { return gridWidth_; }
	int getGridHeight() const { return gridHeight_; }
	int getGridCountX() const { return gridCountX_; }
	int getGridCountY() const { return gridCountY_; }	

	void setGridSize(const int w, const int h);
	
protected:
	int gridWidth_;
	int gridHeight_;
	int gridCountX_;
	int gridCountY_;	
};

#define gg GameGlobal::getInstance()

#endif
