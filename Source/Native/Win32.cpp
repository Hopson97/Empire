#include "Win32.h"

#ifdef __WIN32

    namespace
    {
        WORD _default;
        bool _first = true;
    }

    std::ostream& operator<< (std::ostream& stream, TextColour t)
    {
        if(_first)
        {
            _first = false;
            CONSOLE_SCREEN_BUFFER_INFO Info;
            GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
            _default = Info.wAttributes;
        }

        if(t == TextColour::Default)
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _default);
        else
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)t);
        return stream;
    }

#endif // __WIN32
