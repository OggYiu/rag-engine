#include "Kernel.h"

#include <iostream>
#include <memory>
#include <libgen.h>
// #include<stdlib.h>
#include "Helper.h"
#include "Settings.h"
#include "Page.h"
#include "Page_Default.h"
#include "MouseEvent.h"
#include "KeyboardEvent.h"
#include "DebugConsole.h"
// #include "sdl-widgets.h"

static Kernel s_kernel;

Kernel::Kernel()
	: renderer_(nullptr)
	, window_(nullptr)
	, font_(nullptr)
	, _dt(0)
	, _updated(false)
	, _quit(false)
	, currentPage_(nullptr)
	, nextPage_(nullptr)
	, _bgRed(255)
	, _bgGreen(255)
	, _bgBlue(255)
	, pageContainer_(nullptr)
	, debugContainer_(nullptr)
	, debugConsole_(nullptr)
{
	for (int i=0; i<GLYPH_SIZE; ++i)
	{
		glyphs_[i] = nullptr;
	}
}

Kernel::~Kernel()
{
//	std::cout << "deleting stage" << std::endl;
	SAFE_RELEASE(stage_);
//	std::cout << "finished deleting stage" << std::endl;	
	// if (nextPage_ != nullptr)
	// {
	// 	delete nextPage_;
	// 	nextPage_ = nullptr;
	// }

	free_font();
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	window_ = nullptr;
	renderer_ = nullptr;

	IMG_Quit();
	TTF_Quit();
	SDL_Quit();

//	std::cout << "exit program" << std::endl;
}

bool Kernel::initSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "sdl init failed: " << std::endl;
		showSDLError();
		return false;
	}

	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0"))
	{
		std::cout << "sdl hint render scale quality set failed" << std::endl;
		showSDLError();
		return false;
	}
	
	// start SDL_ttf
	if(TTF_Init()==-1)
	{
		printf("TTF_Init: %s\n", TTF_GetError());
		return 2;
	}
	// atexit(free_font); /* remember to free any loaded font and glyph cache */

// create window
	window_ = SDL_CreateWindow(settings_.winName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, settings_.screenWidth, settings_.screenHeight, SDL_WINDOW_SHOWN);

	if (window_ == nullptr)
	{
		std::cout << "window count not be created" << std::endl;
		showSDLError();
		return false;
	}

	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer_ == nullptr)
	{
		std::cout << "renderer could not be created!" << std::endl;
		showSDLError();
		return false;
	}
	
	SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		std::cout << "SDL_image could not initialize" << std::endl;
		showSDLError();
		return false;
	}

	return true;
}

bool Kernel::exec(int argc __attribute__((unused)), char* argv[], const Settings& settings, Page* startPage)
{
	baseDir_ = dirname(argv[0]);
//	std::cout << "base dpir: " << baseDir_ << std::endl;
	
	settings_ = settings;
	setBackgroundColor(settings_.bgRed, settings_.bgGreen, settings_.bgBlue);	
	if (!initSDL())
	{
		return false;
	}

	if (startPage == nullptr)
	{
		startPage = new Page_Default();
	}

	nextPage_ = startPage;
	return loop();
}

bool Kernel::loop()
{
	SDL_Event e;

//	const double timePerFrame = 1.0 / settings_.frameRate;
	double timeSinceLastUpdate = 0;

	create();

	while (!_quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				_quit = true;
			}
			else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP )
			{
				std::unique_ptr<KeyboardEvent> ptr = std::unique_ptr<KeyboardEvent>( new KeyboardEvent( e.type == SDL_KEYDOWN? KeyboardEvent::KEY_DOWN : KeyboardEvent::KEY_UP, e.key.timestamp, e.key.keysym.sym, (int)e.key.keysym.mod, (int)e.key.repeat ) );
				stage_->dispatchEvent( *ptr.get() );
			}
			else if (e.type == SDL_MOUSEMOTION)
			{
				int mouseX, mouseY;
				SDL_GetMouseState(&mouseX, &mouseY);
				std::unique_ptr<MouseEvent> ptr = std::unique_ptr<MouseEvent>(new MouseEvent(MouseEvent::MOUSE_MOVE, mouseX, mouseY));
				stage_->dispatchEvent(*ptr.get());
			}
			else if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				int mouseX, mouseY;
				SDL_GetMouseState(&mouseX, &mouseY);
				std::unique_ptr<MouseEvent> ptr = std::unique_ptr<MouseEvent>(new MouseEvent(MouseEvent::MOUSE_DOWN, mouseX, mouseY));
				stage_->dispatchEvent(*ptr.get());
			}
			else if (e.type == SDL_MOUSEBUTTONUP)
			{
				int mouseX, mouseY;
				SDL_GetMouseState(&mouseX, &mouseY);
				std::unique_ptr<MouseEvent> ptr = std::unique_ptr<MouseEvent>(new MouseEvent(MouseEvent::MOUSE_UP, mouseX, mouseY));
				stage_->dispatchEvent(*ptr.get());
			}
		}

		std::chrono::time_point<std::chrono::system_clock> now;
		now = std::chrono::system_clock::now();
		if (!_updated)
		{
			_lastClock = now;
			_updated = true;
		}
		std::chrono::duration<double> elapsed_seconds = now - _lastClock;
		_lastClock = now;
		timeSinceLastUpdate += elapsed_seconds.count();

//		std::cout << "accum: " << accum << std::endl;
//		std::cout << "dt: " << _dt << std::endl;
//		std::cout << "timeperframe: " << timePerFrame << std::endl;
//		while (timeSinceLastUpdate > timePerFrame)
		{
//			timeSinceLastUpdate -= timePerFrame;
//			std::cout << "update" << std::endl;
//			update(timePerFrame);
//			static double accum = 0;
//			accum += timeSinceLastUpdate;
//			std::cout << "accum: " << accum << std::endl;
//			update(timeSinceLastUpdate);
			update(elapsed_seconds.count());			
		}
		
//		std::cout << "render" << std::endl;		
		render();
		
//		update();
//		render();
	}

	return true;
}

void Kernel::create()
{
//	stage_ = std::unique_ptr<Stage>(new Stage());
	stage_ = new Stage();

	pageContainer_ = new DisplayObjectContainer();
	stage_->addChild(pageContainer_);

	debugContainer_ = new DisplayObjectContainer();
	stage_->addChild(debugContainer_);

	// init debug console
	debugConsole_ = new DebugConsole();
	debugContainer_->addChild(debugConsole_);

	getStage().addEventListener( KeyboardEvent::KEY_DOWN, bindEventHandler( &Kernel::eventHandler, this ), this );
	getStage().addEventListener( KeyboardEvent::KEY_UP, bindEventHandler( &Kernel::eventHandler, this ), this );
}

void Kernel::free_font()
{
	if (font_ != nullptr)
		TTF_CloseFont(font_);
	font_= nullptr;
	free_glyphs();
}

void Kernel::free_glyphs()
{
	int i;

	for(i=0; i<128; i++)
	{
		if(glyphs_[i])
			SDL_FreeSurface(glyphs_[i]);
		glyphs_[i]=0;
	}
}

bool Kernel::eventHandler( const Event& event )
{
	if ( event.isEqual( KeyboardEvent::KEY_DOWN ) || event.isEqual( KeyboardEvent::KEY_UP ) ) {
		bool isDown = event.isEqual( KeyboardEvent::KEY_DOWN );
		KeyboardEvent* e = (KeyboardEvent*)&event;
		switch ( e->getKeycode() ) {
		case SDLK_ESCAPE:
			_quit = true;
			break;
		case SDLK_BACKQUOTE:
			if ( isDown ) {
				toggleDebugConsoleVisible();
			}
			break;
		}
	}

	return true;
}

void Kernel::toggleDebugConsoleVisible()
{
	debugConsole_->setVisible( !debugConsole_->isVisible() );
	// std::cout << debugConsole_->isVisible() << std::endl;
}

void Kernel::addDebugMsg( const std::string& msg, const Uint32 color )
{
	debugConsole_->addDebugMsg( msg, color );
}

void Kernel::update(const double dt)
{
	_dt = dt;
//	std::cout << "update at: " << dt << std::endl;

	stage_->update(dt);
	// if (currentPage_ != nullptr)
	// {
	// 	// std::cout << "update current page"<< std::endl;
	// 	currentPage_->update(_dt);
	// }
	
	// change to next page if there is one
	if (nextPage_ != nullptr)
	{
		Page* targetPage = nextPage_;
		nextPage_ = nullptr;
		setPage(targetPage);
	}
}

void Kernel::render()
{
	SDL_SetRenderDrawColor( kernel.getRenderer(), _bgRed, _bgGreen, _bgBlue, 255 );
	SDL_RenderClear(kernel.getRenderer());
	
	// if (currentPage_ != nullptr && currentPage_->isVisible() != false)
	// {
	// 	currentPage_->render();
	// }
	stage_->render();
	SDL_RenderPresent(kernel.getRenderer());
}

void Kernel::changePage(Page* page)
{
	nextPage_ = page;
}

void Kernel::setPage(Page* page)
{
	if (currentPage_ != nullptr)
	{
		pageContainer_->removeChild(currentPage_);
		delete currentPage_;
		currentPage_ = nullptr;
	}
	
	currentPage_ = page;
	pageContainer_->addChild(currentPage_);
	currentPage_->enter();
}

SDL_Window* Kernel::getWindow()
{
	return window_;
}

std::string Kernel::getBaseDir() const
{
	return baseDir_;
}

void Kernel::setBackgroundColor(const Uint8 red, const Uint8 green, const Uint8 blue)
{
	_bgRed = red;
	_bgGreen = green;
	_bgBlue = blue;
}

Kernel& Kernel::getInstance()
{
	return s_kernel;
}

Stage& Kernel::getStage() const
{
//	return *stage_.get();
	return *stage_;
}

int Kernel::getScreenWidth() const
{
	int w = 0;
	int h = 0;
	SDL_GetWindowSize(window_, &w, &h);
	return w;
}

int Kernel::getScreenHeight() const
{
	return settings_.screenHeight;
}

bool Kernel::isQuit()
{
	return _quit;
}

void Kernel::quit()
{
	_quit = true;
}
