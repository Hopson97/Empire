#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

constexpr unsigned WIDTH = 1280;
constexpr unsigned HEIGHT = 720;

unsigned getIndex(unsigned x, unsigned y);

template<typename F>
void cellForEach(F f)
{
    for (unsigned y = 0; y < HEIGHT; y++)
    {
        for (unsigned x = 0; x < WIDTH; x++)
        {
            f(x, y);
        }
    }
}



#endif // COMMON_H_INCLUDED
