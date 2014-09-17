#ifndef __TIMER_H__
#define __TIMER_H__

#include <SDL.h>

class Timer
{
public:
	//Initializes variables
	Timer();
	~Timer();	

	//The various clock actions
	void start();
	void stop();
	void pause();
	void unpause();

	//Gets the timer's time
	Uint32 getTicks();
	
	//Checks the status of the timer
	bool isStarted();
	bool isPaused();

private:
	//The clock time when the timer started
	Uint32 startTicks_;

	//The ticks stored when the timer was paused
	Uint32 pausedTicks_;

	//The timer status
	bool paused_;
	bool started_;
};

#endif
