#ifndef TREESIMULATOR_ERROR
#define TREESIMULATOR_ERROR

#include <exception>

namespace tree
{
    class error : public std::exception
    {
        const char* m_message;

    public:
        /**
         * Constructor.
         */
        error(const char* message);

        /**
         * Returns the explanatory string.
         */
        virtual const char* what() const noexcept(true) override;
    };
}

#endif
