#include "Win32.h"

#ifdef __WIN32

    std::ostream& operator<< (std::ostream& stream, TextColour t)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)t);
        return stream;
    }

#else

    std::ostream& operator<< (std::ostream& stream, TextColour t)
    {
        return stream;
    }

#endif // __WIN32
