#ifndef TREESIMULATOR_ERROR_HPP
#define TREESIMULATOR_ERROR_HPP

#include <exception>

namespace tree
{
    class Error : public std::exception
    {
        const char* m_message;

    public:
        /**
         * Constructor.
         */
        Error(const char* message);

        /**
         * Returns the explanatory string.
         */
        virtual const char* what() const noexcept(true) override;
    };
}

#endif
