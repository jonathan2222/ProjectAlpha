#include "Timer.h"

pa::Timer::Timer() : dt(0.0f), isRunning(false)
{
	start();
}

pa::Timer::~Timer()
{
}

void pa::Timer::start()
{
	this->isRunning = true;
	this->startTime = std::chrono::high_resolution_clock::now();
	this->currTime = this->startTime;
	this->preTime = this->startTime;
	this->dt = 0.0f;
}

void pa::Timer::stop()
{
	this->isRunning = false;
	this->currTime = std::chrono::high_resolution_clock::now();
	this->dt = std::chrono::duration<float>(this->currTime - this->startTime).count();
	this->preTime = this->currTime;
}

void pa::Timer::update()
{
	if (this->isRunning)
	{
		this->currTime = std::chrono::high_resolution_clock::now();
		using sec = std::chrono::duration<float>;
		this->dt = std::chrono::duration_cast<sec>(this->currTime - this->preTime).count();
		this->preTime = this->currTime;
	}
}

float pa::Timer::getTime()
{
	using sec = std::chrono::duration<float>;
	return std::chrono::duration_cast<sec>(this->currTime - this->startTime).count();
}

float pa::Timer::getDeltaTime() const
{
	return this->dt;
}