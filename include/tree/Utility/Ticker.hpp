#ifndef TREESIMULATOR_UTILITY_TICKER_HPP
#define TREESIMULATOR_UTILITY_TICKER_HPP

namespace tree
{
    class Ticker
    {
        unsigned int now;
        unsigned int max;

    public:
        /**
         * Constructor.
         */
        Ticker(unsigned int initMax = 1, bool startMaxed = false);

        /**
         * Resets the ticker.
         */
        void reset();

        /**
         * Tick the ticker.
         *
         * Returns true if the max time has been reached.
         */
        bool tick(unsigned int amount = 1);

        /**
         * Whether the ticker has been ticked.
         */
        bool isTicking() const;

        /**
         * Whether the ticker has maxed out.
         */
        bool isMaxed() const;

        /**
         * Get the percentage of completion.
         *
         * Returns a float 0 through 1.
         */
        float percent() const;
    };
}

#endif
