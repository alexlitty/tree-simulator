#include <tree/Utility/Timer.hpp>

// Constructor.
tree::Timer::Timer(unsigned int initMax)
: now(0),
  max(initMax)
{

}

// Resets the timer.
void tree::Timer::reset()
{
    this->now = 0;
}

// Tick the timer.
bool tree::Timer::tick(unsigned int amount)
{
    this->now += amount;
    if (this->now > this->max) {
        this->now = this->max;
    }

    return this->now == this->max;
}

// Whether the timer has been ticked.
bool tree::Timer::isTicking() const
{
    return this->now > 0;
}

// Get the percentage of completion.
float tree::Timer::percent() const
{
    return static_cast<float>(this->now) / static_cast<float>(this->max);
}
