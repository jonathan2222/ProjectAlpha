#ifndef PA_TIMER_H
#define PA_TIMER_H

#include <chrono>

namespace pa
{

	class Timer
	{
	public:
		// Will start the timer when created.
		Timer();
		virtual ~Timer();

		// Start the timer.
		void start();

		// Stop the timer. And calculate the delta time from start to stop. 
		void stop();

		// Calculate delta time from preivous update call.
		void update();

		// The time from starting the timer.
		float getTime();

		// The time from previous update.
		float getDeltaTime() const;

	private:
		float dt;
		std::chrono::time_point<std::chrono::steady_clock> startTime;
		std::chrono::time_point<std::chrono::steady_clock> preTime;
		std::chrono::time_point<std::chrono::steady_clock> currTime;
		bool isRunning;
	};
}

#endif