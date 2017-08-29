#ifndef WIN32_H_INCLUDED
#define WIN32_H_INCLUDED

#include <iostream>

#ifdef __WIN32
    #include "windows.h"
    enum class TextColour
    {
        Default           = -1
        Black             = 0,
        DarkBlue          = FOREGROUND_BLUE,
        DarkGreen         = FOREGROUND_GREEN,
        DarkCyan          = FOREGROUND_GREEN    | FOREGROUND_BLUE,
        DarkRed           = FOREGROUND_RED,
        DarkMagenta       = FOREGROUND_RED      | FOREGROUND_BLUE,
        DarkYellow        = FOREGROUND_RED      | FOREGROUND_GREEN,
        DarkGrey          = FOREGROUND_RED      | FOREGROUND_GREEN | FOREGROUND_BLUE,
        Grey              = FOREGROUND_INTENSITY,
        Blue              = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
        Green             = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
        Cyan              = FOREGROUND_INTENSITY | FOREGROUND_GREEN     | FOREGROUND_BLUE,
        Red               = FOREGROUND_INTENSITY | FOREGROUND_RED,
        Magenta           = FOREGROUND_INTENSITY | FOREGROUND_RED       | FOREGROUND_BLUE,
        Yellow            = FOREGROUND_INTENSITY | FOREGROUND_RED       | FOREGROUND_GREEN,
        White             = FOREGROUND_INTENSITY | FOREGROUND_RED       | FOREGROUND_GREEN | FOREGROUND_BLUE,
    };

    std::ostream& operator<< (std::ostream& stream, TextColour t);

///@TODO This stuff for other OS
#else
    enum class TextColour
    {
        Default           = 39,
        Black             = 30,
        DarkBlue          = 34,
        DarkGreen         = 32,
        DarkCyan          = 36,
        DarkRed           = 31,
        DarkMagenta       = 35,
        DarkYellow        = 33,
        DarkGrey          = 90,
        Grey              = 37,
        Blue              = 94,
        Green             = 92,
        Cyan              = 96,
        Red               = 91,
        Magenta           = 95,
        Yellow            = 33,
        White             = 97,
    };

    std::ostream& operator<< (std::ostream& stream, TextColour t);

#endif // __WIN32

#endif // WIN32_H_INCLUDED
