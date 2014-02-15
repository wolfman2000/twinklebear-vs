#include "Timer.hpp"
#include <SDL.h>

Timer::Timer() : _startTicks(0), _pausedTicks(0), _isStarted(false), _isPaused(false) {
}

void Timer::Start() {
	_isStarted = true;
	_isPaused = false;
	_startTicks = SDL_GetTicks();
}

void Timer::Stop() {
	_isStarted = false;
	_isPaused = false;
}