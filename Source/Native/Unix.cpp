#include "Unix.h"

#if defined(__unix__) || defined(__unix)

    std::ostream& operator<< (std::ostream& stream, TextColour t)
    {
        stream << "\e[" + std::to_string((int)t) + "m";
        return stream;
    }

#endif // __unix__ || __unix
