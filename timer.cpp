#include <chrono> // for std::chrono functions
#include "timer.h"


void Timer::start()
{
	m_beg = Clock::now();
}

double Timer::stop() const
{
	return 1e3*std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
}