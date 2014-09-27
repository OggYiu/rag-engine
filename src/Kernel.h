#ifndef __KERNAL_H__
#define __KERNAL_H__

#include <memory>
#include <ctime>
#include <chrono>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Settings.h"
#include "Stage.h"
#include "Object.h"
#include "Event.h"

#define GLYPH_SIZE 128

class Page;
class DebugConsole;

class Kernel : public Object
{
public:
	Kernel();
	~Kernel();

public:
	bool exec(int argc, char* argv[], const Settings& settings, Page* startPage = nullptr);

	void changePage(Page* page);
	
	bool isQuit();
	void quit();
	void setBackgroundColor(const Uint8 red, const Uint8 green, const Uint8 blue);

	// getter and setter
	inline SDL_Renderer* getRenderer() { return renderer_; }
	SDL_Window* getWindow();
	int getScreenWidth() const;
	int getScreenHeight() const;
	std::string getBaseDir() const;
	Stage& getStage() const;
	void addDebugMsg( const std::string& msg, const Uint32 color = 0xFF000000 );

private:
	bool initSDL();
	bool loop();
	virtual void update(const double dt);
	void render();
	void setPage(Page* page);
	void create();
	void free_font();
	void free_glyphs();
	bool eventHandler( const Event& event );
	void toggleDebugConsoleVisible();
	
private:
	SDL_Renderer* renderer_;
	SDL_Window* window_;
	TTF_Font* font_;
	SDL_Surface* glyphs_[GLYPH_SIZE];
	std::chrono::time_point<std::chrono::system_clock> _lastClock;
	double _dt;
	bool _updated;
	bool _quit;
	Page* currentPage_;
	Page* nextPage_;
	Settings settings_;
	Uint8 _bgRed;
	Uint8 _bgGreen;
	Uint8 _bgBlue;
	std::string baseDir_;
//	std::unique_ptr<Stage> stage_;
	Stage* stage_;	
	DisplayObjectContainer* pageContainer_;
	DisplayObjectContainer* debugContainer_;	
	DebugConsole* debugConsole_;
	
public:
	static Kernel& getInstance();
};

#define kernel Kernel::getInstance()
#endif
