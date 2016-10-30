#ifndef TREESIMULATOR_UTILITY_TIMER_HPP
#define TREESIMULATOR_UTILITY_TIMER_HPP

namespace tree
{
    class Timer
    {
        unsigned int now;
        unsigned int max;

    public:
        /**
         * Constructor.
         */
        Timer(unsigned int initMax = 1);

        /**
         * Resets the timer.
         */
        void reset();

        /**
         * Tick the timer.
         *
         * Returns true if the max time has been reached.
         */
        bool tick(unsigned int amount = 1);

        /**
         * Whether this timer has been ticked.
         */
        bool isTicking() const;

        /**
         * Get the percentage of completion.
         *
         * Returns a float 0 through 1.
         */
        float percent() const;
    };
}

#endif
