#include <tree/Utility/Ticker.hpp>

// Constructor.
tree::Ticker::Ticker(unsigned int initMax, bool startMaxed)
: now(startMaxed ? initMax : 0),
  max(initMax)
{

}

// Resets the ticker.
void tree::Ticker::reset()
{
    this->now = 0;
}

// Tick the ticker.
bool tree::Ticker::tick(unsigned int amount)
{
    this->now += amount;
    if (this->now > this->max) {
        this->now = this->max;
    }

    return this->now == this->max;
}

// Whether the ticker has been ticked.
bool tree::Ticker::isTicking() const
{
    return this->now > 0;
}

// Whether the ticker has maxed out.
bool tree::Ticker::isMaxed() const
{
    return this->now == this->max;
}

// Get the percentage of completion.
float tree::Ticker::percent() const
{
    return static_cast<float>(this->now) / static_cast<float>(this->max);
}
