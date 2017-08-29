#ifndef UNIX_H_INCLUDED
#define UNIX_H_INCLUDED

#ifdef __unix__

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

#endif // __unix__

#endif // UNIX_H_INCLUDED
