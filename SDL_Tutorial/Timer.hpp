#ifndef TIMER_HPP_
#define TIMER_HPP_

// TODO: Make this work using <chrono>

class Timer {
public:
	Timer();
	void Start();
	void Stop();
	void Pause();
	void Unpause();
	int Restart();
	int Ticks() const;
	bool IsStarted() const;
	bool IsPaused() const;

private:
	int _startTicks, _pausedTicks;
	bool _isStarted, _isPaused;
};

#endif