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

void Timer::Pause() {
	if (_isStarted && !_isPaused) {
		_isPaused = true;
		_pausedTicks = SDL_GetTicks() - _startTicks;
	}
}

void Timer::Unpause() {
	if (_isPaused) {
		_isPaused = false;
		_startTicks = SDL_GetTicks() - _pausedTicks;
		_pausedTicks = 0;
	}
}

int Timer::Restart() {
	auto elapsedTicks = Ticks();
	Start();
	return elapsedTicks;
}

int Timer::Ticks() const {
	if (!_isStarted) {
		return 0;
	}

	return _isPaused ? _pausedTicks : SDL_GetTicks() - _startTicks;
}

bool Timer::IsPaused() const {
	return _isPaused;
}

bool Timer::IsStarted() const {
	return _isStarted;
}