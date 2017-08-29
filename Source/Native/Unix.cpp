#include "Unix.h"

#ifdef __unix__

    std::ostream& operator<< (std::ostream& stream, TextColour t)
    {
        stream << "\e[" + std::to_string((int)t) + "m";
        return stream;
    }

#endif // __unix__
