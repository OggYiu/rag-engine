#include "Timer.h"

Timer::Timer()
	: startTicks_( 0 )
    , pausedTicks_( 0 )
    , paused_( false )
    , started_( false )
{
}

Timer::~Timer()
{
}

void Timer::start()
{
    //Start the timer
    started_ = true;

    //Unpause the timer
    paused_ = false;

    //Get the current clock time
    startTicks_ = SDL_GetTicks();
	pausedTicks_ = 0;
}

void Timer::stop()
{
    //Stop the timer
    started_ = false;

    //Unpause the timer
    paused_ = false;

	//Clear tick variables
	startTicks_ = 0;
	pausedTicks_ = 0;
}

void Timer::pause()
{
    //If the timer is running and isn't already paused
    if ( started_ && !paused_ )
    {
        //Pause the timer
        paused_ = true;

        //Calculate the paused ticks
        pausedTicks_ = SDL_GetTicks() - startTicks_;
		startTicks_ = 0;
    }
}

void Timer::unpause()
{
    //If the timer is running and paused
    if ( started_ && paused_ )
    {
        //Unpause the timer
        paused_ = false;

        //Reset the starting ticks
        startTicks_ = SDL_GetTicks() - pausedTicks_;

        //Reset the paused ticks
        pausedTicks_ = 0;
    }
}

Uint32 Timer::getTicks()
{
	//The actual timer time
	Uint32 time = 0;

    //If the timer is running
    if ( started_ )
    {
        //If the timer is paused
        if ( paused_ )
        {
            //Return the number of ticks when the timer was paused
            time = pausedTicks_;
        }
        else
		{
            //Return the current time minus the start time
            time = SDL_GetTicks() - startTicks_;
        }
    }

    return time;
}

bool Timer::isStarted()
{
	//Timer is running and paused or unpaused
    return started_;
}

bool Timer::isPaused()
{
	//Timer is running and paused
    return paused_ && started_;
}
