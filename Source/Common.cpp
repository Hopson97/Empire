#include "Common.h"

#include <vector>

#include "Random.h"

unsigned getIndex(unsigned width, unsigned x, unsigned y)
{
    return y * width + x;
}
